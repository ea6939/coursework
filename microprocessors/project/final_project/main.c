/*!
* @file main.c
* @author Clark Gredona 260458872
* @author Harsh Aurora 260394216
* @author Loren Lugosch 260404057
* @author Radhika Chandra 260427945
* @brief ECSE 426 final project main program.
*/


#include "arm_math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "stm32f4xx.h"
#include "cmsis_os.h"
#include "g2_mems.h"
#include "g2_keypad.h"
#include "g2_wireless.h"
#include "g2_button.h"
#include "lcd.h"
#include "cc2500.h"
#include "g2_servo.h"

#define LENGTH 20
#define MASTER_MODE 0 // send data/commands to slave board
#define SLAVE_MODE 1 // receive data/commands from master board



typedef enum {
    MIMIC_MODE = 0,
    DIRECT_MODE = !MIMIC_MODE
} g2_control_mode;

/*
Structs used for mail
*/

typedef struct {
    g2_control_mode mode;
    uint8_t pitch;
		uint8_t roll;
		uint16_t time; // in ms
} g2_packet_t;

typedef struct {
int8_t pitch;
int8_t roll;
uint16_t time;	
} g2_input_t;


osMailQDef(packet_mail_box, sizeof(g2_packet_t), g2_packet_t);
osMailQId  packet_mail_box;

osMailQDef(input_mail_box, sizeof(g2_input_t), g2_input_t);
osMailQId input_mail_box;


void thread_user_input(void const * argument);
void thread_display(void const * argument);
void thread_wireless_master(void const * argument);
void thread_wireless_slave(void const * argument);
void thread_direct_control(void const * argument);
void thread_mimicking(void const * argument);
void thread_motor(void const * argument);

uint8_t result, status, status_test;
uint8_t mode = MASTER_MODE;
g2_control_mode control_mode = DIRECT_MODE;
char chars[LENGTH];
char sending_flag, choose;

char pitch_chars[3] = {'_','_','_'};
char roll_chars[3] = {'_','_','_'};
char time_chars[4] = {'_','_','_','_'};


uint8_t datums[5], tx_num = 0, rx_num = 0, ovrflo = 0, Rbuf[25], Wbuf[25];
float current_pitch, current_roll = 0.0;

osMutexId char_mutex;
osMutexId SPI_mutex;
osMutexDef(char_mutex);
osMutexDef(SPI_mutex);

//! Thread structure for above thread
osThreadDef(thread_user_input, osPriorityNormal, 1, 0);
osThreadDef(thread_display, osPriorityNormal, 1, 0);
osThreadDef(thread_wireless_master, osPriorityNormal, 1, 0);
osThreadDef(thread_wireless_slave, osPriorityNormal, 1, 0);
osThreadDef(thread_direct_control, osPriorityNormal, 1, 0);
osThreadDef(thread_mimicking, osPriorityNormal, 1, 0);


// ID for thread
osThreadId tid_thread_user_input;
osThreadId tid_thread_display;
osThreadId tid_thread_wireless_master;
osThreadId tid_thread_wireless_slave;
osThreadId tid_thread_direct_control;
osThreadId tid_thread_mimicking;


uint8_t buf = 0;

/*!
 @brief handler for MEMS timer interrupts
 */
void TIM5_IRQHandler(void){
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET){
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
		osSignalSet(tid_thread_wireless_master,0x02);
	}
}

void g2_raw2struct(uint8_t * str, g2_packet_t * pkt) {
	uint8_t loop, bit, count, temp, index;

	temp = 0;
	index = 0;
	for(bit=0 ; bit<8 ; bit++) {
		count = 0;
		for(loop=0 ; loop<5 ; loop++)
			if(str[(index+loop)] & (0x01<<bit))
				count++;
		if(count>2)
			temp += 0x01<<bit;
	}

	count = 0;
	for(bit = 0; bit < 8 ; bit++)
		if(temp & (0x01<<bit))
			count++;

	if(count <= 4)
		pkt->mode = MIMIC_MODE;
	else
		pkt->mode = DIRECT_MODE;

	temp = 0;
	index += 5;
	for(bit=0 ; bit<8 ; bit++) {
		count = 0;
		for(loop=0 ; loop<5 ; loop++)
			if(str[(index+loop)] & (0x01<<bit))
				count++;
		if(count>2)
			temp += 0x01<<bit;
	}
	pkt->pitch = temp;

	temp = 0;
	index += 5;
	for(bit=0 ; bit<8 ; bit++) {
		count = 0;
		for(loop=0 ; loop<5 ; loop++)
			if(str[(index+loop)] & (0x01<<bit))
				count++;
		if(count>2)
			temp += 0x01<<bit;
	}
	pkt->roll = temp;

	temp = 0;
	index += 5;
	for(bit=0 ; bit<8 ; bit++) {
		count = 0;
		for(loop=0 ; loop<5 ; loop++)
			if(str[(index+loop)] & (0x01<<bit))
				count++;
		if(count>2)
			temp += 0x01<<bit;
	}
	pkt->time = temp<<8;

	temp = 0;
	index += 5;
	for(bit=0 ; bit<8 ; bit++) {
		count = 0;
		for(loop=0 ; loop<5 ; loop++)
			if(str[(index+loop)] & (0x01<<bit))
				count++;
		if(count>2)
			temp += 0x01<<bit;
	}
	pkt->time += temp;
}

void g2_struct2raw(g2_packet_t *str, uint8_t *pkt) {
	uint8_t loop;

	for(loop=0 ; loop<5 ; loop++) {
		if(str->mode == DIRECT_MODE)
			*pkt = 0xFF;
		else
			*pkt = 0x00;
		pkt++;
	}

	for(loop=0 ; loop<5 ; loop++){
		*pkt = str->pitch;
		pkt++;
	}

	for(loop=0 ; loop<5 ; loop++) {
		*pkt = str->roll;
		pkt++;
	}

	for(loop=0 ; loop<5 ; loop++) {
		*pkt = ((str->time>>8)&0x00ff); // MSB 
		pkt++;
	}
	
	for(loop=0 ; loop<5 ; loop++) {
		*pkt = (str->time&0x00ff); // LSB
			if(loop!=4)
		pkt++;
	}
}

/*!
 @brief Program entry point
 */
int main (void) {

    // Mutex for display
		CC2500_Init();
    char_mutex = osMutexCreate(osMutex(char_mutex));
    SPI_mutex = osMutexCreate(osMutex(SPI_mutex));

    // Start threads
    if (mode == MASTER_MODE) {
			
				input_mail_box = osMailCreate(osMailQ(input_mail_box), NULL);
        tid_thread_display = osThreadCreate(osThread(thread_display), NULL);
        tid_thread_wireless_master = osThreadCreate(osThread(thread_wireless_master), NULL);
        tid_thread_user_input = osThreadCreate(osThread(thread_user_input), NULL);
      
      // Start by signalling the display (so it's not blank when we turn it on)
    osSignalSet(tid_thread_display,0x01);
      
    }

    else {
        servo_setup();
				servo_setup2();
				packet_mail_box = osMailCreate(osMailQ(packet_mail_box), NULL);
        tid_thread_wireless_slave = osThreadCreate(osThread(thread_wireless_slave), NULL);
				tid_thread_mimicking = osThreadCreate(osThread(thread_mimicking), NULL);
				tid_thread_direct_control = osThreadCreate(osThread(thread_direct_control), NULL);
    }

    osDelay(osWaitForever);
}

void thread_master_test (void const *argument) {
	//CC2500_Init();
	//CC2500_Strobe(CC2500_CMDSTROBE_SIDLE, RX);
	uint8_t pktlen = 16, address = 0x69;
	uint8_t datum[16], data[16], i = 0;
  for(i=0; i<16; i++) { datum[i] = (0xf0+i); data[i] = i; }
	int bob = 0;
	
	while(1) {
			CC2500_Strobe(CC2500_CMDSTROBE_SIDLE, TX);
		  CC2500_Write(&address,0x3F,0x01);
      if (bob) CC2500_Write(datum,0x3F,pktlen);
			else CC2500_Write(data,0x3F,pktlen);
      CC2500_Strobe(CC2500_CMDSTROBE_STX, TX);
			osDelay(1000);
		
			if (bob == 0) bob = 1;
			else bob = 0;
  }
}

/**
  * @brief  Thread for master mode operation
  * @param  argument: not used   
  * @retval None
  */
void thread_wireless_master (void const *argument) {
    user_button_GPIO_setup();
    button_interrupt_setup();
		MEMS_TIM5_Configuration();
		g2_LIS3DSH_setup();
		g2_packet_t pkt;
    uint8_t address = 0x69;
		osEvent evt;

    while(1) {
       // osSignalWait(0x01, osWaitForever);
			
			if (control_mode == DIRECT_MODE) {
				evt = osMailGet(input_mail_box, 10); // time to wait?
				 if (evt.status == osEventMail) {
						g2_input_t * recv_input = evt.value.p;
						pkt.pitch = recv_input->pitch;
						pkt.roll = recv_input->roll;
						pkt.time = recv_input->time;
						pkt.mode = DIRECT_MODE;
            osMailFree(input_mail_box, recv_input);
					 
					  osMutexWait(SPI_mutex, osWaitForever);

            g2_struct2raw(&pkt, Wbuf);
						CC2500_Strobe(CC2500_CMDSTROBE_SIDLE, TX);
						CC2500_Write(&address, 0x3F, 1);
						CC2500_Write(Wbuf, 0x3F, 25);
						CC2500_Strobe(CC2500_CMDSTROBE_STX, TX);

						osMutexRelease(SPI_mutex);
				 }
			} else {
					osSignalWait(0x02,osWaitForever);
					update_orientation();
					pkt.pitch = get_pitch() + 90;
					pkt.roll = get_roll() + 90;
					pkt.time = 0;
					pkt.mode = MIMIC_MODE;
				
				      osMutexWait(SPI_mutex, osWaitForever);

							g2_struct2raw(&pkt, Wbuf);
							CC2500_Strobe(CC2500_CMDSTROBE_SIDLE, TX);
							CC2500_Write(&address, 0x3F, 1);
							CC2500_Write(Wbuf, 0x3F, 25);
							CC2500_Strobe(CC2500_CMDSTROBE_STX, TX);	

							osMutexRelease(SPI_mutex);
				
			}
				
			
 
    }
}

/**
  * @brief  Operation of board in slave mode
  * @param  Argument: not used   
  * @retval None
  */
void thread_wireless_slave (void const *argument) {
		CC2500_Strobe(CC2500_CMDSTROBE_SIDLE, RX);
		uint8_t address;
		g2_packet_t pkt;
		
		while (1) {
			CC2500_Strobe(CC2500_CMDSTROBE_SRX, RX);
      osSignalWait(0x01, osWaitForever);
			
			/* correct number of bytes in the buffer */
			if(CC2500_ReadStatusReg(CC2500_STATUSREG_RXBYTES_ADDR) == 26) { 
				CC2500_Read(&address,0x3F,1);
				/* if the address is correct */
				if(address == 0x69) { 
					CC2500_Read(Rbuf,0x3F,25);
			
					g2_raw2struct(Rbuf, &pkt);
			
					g2_packet_t * packet_s = osMailAlloc(packet_mail_box,osWaitForever);
					packet_s->pitch = pkt.pitch;
					packet_s->roll = pkt.roll;
					packet_s->time = pkt.time;
					packet_s->mode = pkt.mode;
					// Send motor commands to appropriate thread
					osMailPut(packet_mail_box, packet_s);
					if (packet_s->mode == MIMIC_MODE) {
						osSignalSet(tid_thread_mimicking, 0x04);
					} 
					else {
						osSignalSet(tid_thread_direct_control, 0x01);
					}
					osDelay(pkt.time);
				}
				/* address was wrong */
				else {
					CC2500_Strobe(CC2500_CMDSTROBE_SFRX, RX);
				}
			}
			/* wrong number of bytes in buffer */
			else { 
				CC2500_Strobe(CC2500_CMDSTROBE_SFRX, RX);
			}
		}
}

/**
  * @brief  Thread for keypad
  * @param  Argument: not used   
  * @retval None
  */
void thread_user_input (void const *argument) {
    g2_keypad_init();
    UserInputState state = WAIT_FOR_INPUT;
    char user_input;
    uint16_t input_count = 0;
    int new_time;
    char temp[3];
  
		g2_input_t * input_s;
		uint8_t datum_count;

    while (1) {
			
        switch(state) {				
				if (control_mode != DIRECT_MODE) {
					//osSignalSet(tid_thread_display,0x01); // signal the LCD (to display "MIMIC MODE")
					osDelay(100);
					break;
				}
				
        case WAIT_FOR_INPUT:
            user_input = g2_read_keypad();
						
            // handle no input
            if (user_input == NO_KEYPAD_INPUT) {
                osDelay(10);
                break;
            }

            // handle non-numeric input
            if (user_input == 'A' || user_input == 'B' || user_input == 'C' || user_input == 'D' || user_input == '*' || user_input == '#') {
                state = INPUT_ERROR;
                
								user_input = KEYPAD_ERROR;
							
							
            }

            // handle correct input
            else {
                                
                state = WAIT_FOR_BUTTON_RELEASE;
            }
						
						//osMutexWait(char_mutex, osWaitForever);
						if (input_count > 0 && input_count < 3) {
							
							
							pitch_chars[input_count] = user_input;
									
						} else if (input_count > 3 && input_count < 6) {
							roll_chars[input_count - 3] = user_input;
						}
						else {
							time_chars[input_count - 6] = user_input;						
						}
						
            //osMutexRelease(char_mutex);
						osSignalSet(tid_thread_display,0x01); // signal the LCD

            osDelay(10);
            break;

        case WAIT_FOR_BUTTON_RELEASE: 
            user_input = g2_read_keypad();

            // button still being pushed
            if (user_input != NO_KEYPAD_INPUT) {
                osDelay(10);
                break;
            }

            // more input left to read
            if (input_count < 9) {
                input_count++;
                state = WAIT_FOR_INPUT;
            } 

            // done reading input
            else {
                input_count = 0;
                state = WAIT_FOR_SEND_COMMAND;
						}
							
            osDelay(10);
            break;
					
        case WAIT_FOR_SEND_COMMAND:
            user_input = g2_read_keypad();
            if (user_input != KEYPAD_SEND_COMMAND) {
                if (user_input == NO_KEYPAD_INPUT) state = WAIT_FOR_SEND_COMMAND;
                else state = SEND_ERROR;
            }
            else {
								
                state = SENDING;
                
            }
            osDelay(10);
            break;

        case INPUT_ERROR:
            // display error message for a moment
						//osMutexWait(char_mutex, osWaitForever);
            sending_flag = KEYPAD_ERROR;
            //osMutexRelease(char_mutex);                
            osSignalSet(tid_thread_display,0x01); // signal the LCD
					
            osDelay(500);
            state = WAIT_FOR_INPUT;
            osDelay(10);
            break;

        case SEND_ERROR:
            // display error message for a moment
						//osMutexWait(char_mutex, osWaitForever);
            sending_flag = KEYPAD_ERROR;
            //osMutexRelease(char_mutex);                
            osSignalSet(tid_thread_display,0x01); // signal the LCD
				
            state = WAIT_FOR_SEND_COMMAND;
            osDelay(10);
            break;

        case SENDING:
            // send stuff to the wireless master thread
							
							strncpy(temp, pitch_chars, 3);
							int new_pitch = atoi(temp);
							
							strncpy(temp, roll_chars, 3);
							int new_roll = atoi(temp);
							
							if (new_pitch > 180 || new_roll > 180) {
								memset(pitch_chars, '_', 3 * sizeof(char));				
								memset(roll_chars, '_', 3 * sizeof(char));							
								memset(time_chars, '_', 4 * sizeof(char));
								state = INPUT_ERROR;
								break;
							}							
							
							new_time = atoi(time_chars);
							
								input_s = osMailAlloc(input_mail_box, osWaitForever);
								input_s->pitch = new_pitch;
								input_s->roll = new_roll;
								input_s->time = new_time;
								osMailPut(input_mail_box, input_s);
              
                memset(pitch_chars, '_', 3 * sizeof(char));							
								memset(roll_chars, '_', 3 * sizeof(char));							
								memset(time_chars, '_', 4 * sizeof(char));
							
								datum_count = (datum_count + 1) % 3;
							
                sending_flag = user_input;
              osSignalSet(tid_thread_display,0x01); // signal the LCD
              
            osDelay(500); // wait for some kind of ACK
            state = WAIT_FOR_INPUT;
            osDelay(10);
            break;

        default: // if undefined state, jump back to input state
            state = WAIT_FOR_INPUT;
            osDelay(10);
            break;
        }

    }
}

/**
  * @brief  Thread for LCD
  * @param  Argument: not used   
  * @retval None
  */
void thread_display (void const *argument) {

    LCD_SettingsTypeDef LCD_SettingsStruct;
    LCD_DisplayTypeDef LCD;

    LCD.DisplayEnable = LCD_ON;
    LCD.CursorBlink = LCD_ON;
    LCD.CursorUnderline = LCD_ON;
    LCD_Init(&LCD);

    LCD_SettingsStruct.IncrDecr = INCREASE;
    LCD_SettingsStruct.DisplayShiftEn = LCD_OFF;
    LCD_SettingsStruct.ShiftSettings = CURSOR_SHIFT;
    LCD_SettingsStruct.ShiftDirection = RIGHT;
    LCD_SettingsStruct.DataLength = BITS_8;
    LCD_SettingsStruct.LineMode = LINES_2;
    LCD_SettingsStruct.CharSize = CHAR_5x7;
    LCD_ConfigureSettings(&LCD_SettingsStruct);
	
	g2_input_t * recv_input; 

    while(1) {
        
        osSignalWait(0x01,osWaitForever);
			if (control_mode == DIRECT_MODE){
        if (sending_flag == KEYPAD_SEND_COMMAND) {
            LCD_ClearDisplay(&LCD);
            LCD_WriteString(&LCD, "SENDING...");
            osDelay(1000);
            LCD_ClearDisplay(&LCD);
						sending_flag = 0;
        }

        else if (sending_flag == KEYPAD_ERROR) {
            LCD_ClearDisplay(&LCD);
            LCD_WriteString(&LCD, "INPUT ERROR");
            osDelay(1000);
            LCD_ClearDisplay(&LCD);
					sending_flag = 0;
        }
        
        LCD_ClearDisplay(&LCD);
				LCD_WriteString(&LCD, "Pitch : ");
			
			//the character buffs are roll, pitch, and time are continguous in memory so this ensures that they are accessed separately
				for (int i = 0; i < 3; i++) {
					LCD_WriteChar(&LCD, pitch_chars[i]);
					
				}
				LCD_WriteString(&LCD, " | Roll : ");
				for (int i = 0; i < 3; i++) {
					LCD_WriteChar(&LCD, roll_chars[i]);
				}
				
				LCD_WriteString(&LCD, " | Time : ");
        for (int i = 0; i < 4; i++) {
					LCD_WriteChar(&LCD, time_chars[i]);
				}

        osDelay(10);
			}
			
			else /* if in mimic mode*/ {
				LCD_ClearDisplay(&LCD);
        LCD_WriteString(&LCD, "MIMIC MODE");
				osDelay(10);
			}

        //osMutexRelease(char_mutex);
    }
}

/**
  * @brief  Thread for moving to coordinates from master user input
  * @param  Argument: not used   
  * @retval None
  */
void thread_direct_control(void const * argument) {

	uint32_t time_step = 20; // 20 ms increments
    //adapted from MBED handbook
    while(1) {
        osSignalWait(0x1, osWaitForever);
				
			//gets mail from the slave thread
        osEvent evt = osMailGet(packet_mail_box, osWaitForever);
        if (evt.status == osEventMail) {
						g2_packet_t * recv_packet = evt.value.p;
					
						float target_pitch = recv_packet->pitch;
						float target_roll = recv_packet->roll;
						float target_time = recv_packet->time;
					
						osMailFree(packet_mail_box, recv_packet);
					
					//computes the slope per increment of time
					float pitch_slope = (target_pitch - current_pitch) / (target_time / time_step);
					float roll_slope = (target_roll - current_roll) / (target_time / time_step);
					int count = 1;
					
					//at every time step, it rotates the computed slope
						for (int i = 0; i < target_time; i += time_step) {
							turn_to_angle(current_pitch + count * pitch_slope);
							turn_to_angle2(current_roll + count * roll_slope);
							count++;
							osDelay(time_step);
						}
						
						current_pitch = target_pitch;
						current_roll = target_roll;
        }
    }
}

/**
  * @brief  Thread for mimicking the orientation of the master board
  * @param  Argument: not used   
  * @retval None
  */
void thread_mimicking(void const * argument) {
	    while(1) {
        //osSignalWait(0x1, osWaitForever);
				
				//receives mail from the slave thread
        osEvent evt = osMailGet(packet_mail_box, osWaitForever);
        if (evt.status == osEventMail) {
						g2_packet_t * recv_packet = evt.value.p;
						turn_to_angle(recv_packet->pitch - 90);
						turn_to_angle2(recv_packet->roll - 90);
						osMailFree(packet_mail_box, recv_packet);
        }
    }
}


/**
  * @brief  Handles button press and toggles control mode
  *  * @retval None
  */
void EXTI0_IRQHandler(void) {
	
		control_mode = !control_mode;
    //osSignalSet(tid_thread_wireless_master, 0x01);
		osSignalSet(tid_thread_display,0x01); 
    EXTI_ClearITPendingBit(EXTI_Line0);
}

/**
  * @brief  Packet received
  *  * @retval None
  */
void EXTI15_10_IRQHandler(void) {
		osSignalSet(tid_thread_wireless_slave, 0x01);
    EXTI_ClearITPendingBit(EXTI_Line11);
}
