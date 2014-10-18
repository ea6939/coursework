/* Taken from project specification */

#ifndef SMARTRF_CC2500_H 
#define SMARTRF_CC2500_H 
 
#define SMARTRF_RADIO_CC2500 
#define SMARTRF_SETTING_GDO0 0x01 // Asserts when above thresh or end of packet is reached, deasserts when RX buffer is empty 
#define SMARTRF_SETTING_FSCTRL1 0x0C//0x12 //Frequency offset = 457kHz 
#define SMARTRF_SETTING_FSCTRL0 0x00 
#define SMARTRF_SETTING_FREQ2 0x5D // 2.433GHz = 0x5D93B1 (* 397)
#define SMARTRF_SETTING_FREQ1 0x93 
#define SMARTRF_SETTING_FREQ0 0xDA // Russian affirmation
#define SMARTRF_SETTING_MDMCFG4 0x0E //0x2D // BW of channel = 541.666kHz 
#define SMARTRF_SETTING_MDMCFG3 0x3B // Baud Rate = 125kb 
#define SMARTRF_SETTING_MDMCFG2 0x73 // before demodulator, MSK modulation, 16/16 sync word bits detected 
#define SMARTRF_SETTING_MDMCFG1 0x72//0x42 / 
#define SMARTRF_SETTING_MDMCFG0 0xF8 // Default Channel Spacing of 200kHz 
#define SMARTRF_SETTING_CHANNR 0x00 // Channel 0 
#define SMARTRF_SETTING_DEVIATN 0x00 //0x01 // 1785kHz 
#define SMARTRF_SETTING_FREND1 0xB6 
#define SMARTRF_SETTING_FREND0 0x10 
#define SMARTRF_SETTING_MCSM0 0x18 // Automatically calibrate When going from IDLE to RX or TX (or FSTXON) check CC2500 datasheet 
//#define SMARTRF_SETTING_MCSM1 0x
#define SMARTRF_SETTING_FOCCFG 0x1D // check datasheet 
#define SMARTRF_SETTING_BSCFG 0x1C 
#define SMARTRF_SETTING_AGCCTRL2 0xC7 
#define SMARTRF_SETTING_AGCCTRL1 0x40 //0x00 
#define SMARTRF_SETTING_AGCCTRL0 0xB0 
#define SMARTRF_SETTING_FSCAL3 0xEA 
#define SMARTRF_SETTING_FSCAL2 0x0A 
#define SMARTRF_SETTING_FSCAL1 0x00 
#define SMARTRF_SETTING_FSCAL0 0x19 //0x11 
#define SMARTRF_SETTING_FSTEST 0x59 
#define SMARTRF_SETTING_TEST2 0x88 
#define SMARTRF_SETTING_TEST1 0x31 
#define SMARTRF_SETTING_TEST0 0x0B 
#define SMARTRF_SETTING_FIFOTHR 0x07 
#define SMARTRF_SETTING_IOCFG2 0x29 
#define SMARTRF_SETTING_IOCFG0 0x01 
#define SMARTRF_SETTING_PKTCTRL1 0x0a//0x04 
#define SMARTRF_SETTING_PKTCTRL0 0x04//0x45 // Variable Packet Length, data whitening, CRC enabled 
#define SMARTRF_SETTING_ADDR 0x69 // Global Broadcast Address 
#define SMARTRF_SETTING_PKTLEN 0x1A // size of g2_packet_t 
 
 
 
#endif
