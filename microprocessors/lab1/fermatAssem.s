	AREA text, CODE, READONLY
	EXPORT fermatAssem
fermatAssem
	; put F1 in R1 and F2 in R2
	; MOV R3, #8217 ; dummy value of N
	; POP {R3} ; assumes that the top of the stack is N
	PUSH {R4-R12}
	MOV R3, R0
	CMP R3, #0
	BLE nonPositiveCase
	AND R4, R3, #0x00000001
	CMP R4, #1
	BNE evenCase ; if the last bit of R3 isn't 1, R3 is even
	B oddCase
nonPositiveCase
	; if N <= 0, f1 := f2 := 0
	MOV R1, #0
	MOV R2, #0
	B branchBack
evenCase
	; if N even, f1 := 2, f2 := N/2
	MOV R1, #2
	SDIV R2, R3, R1
	B branchBack
oddCase
	; R5 = x
	; change Rmode to ceiling
	MRS R8, FPSCR
	AND R8, #0xff7fffff
	ORR R8, #0x00400000
	MSR FPSCR, R8
	
	VMOV.F32 S0, R3
	VCVT.F32.S32 S0, S0 ; convert int to float
	VSQRT.F32 S0, S0
	VCVTR.S32.F32 S0, S0 ; convert float to int
	VMOV.F32 R5, S0 
	MUL R6, R5, R5

	; check whether 1 * 1 < R3, then 2 * 2, etc.
	; if R5^2 > R3, ceil(sqrt(R3)) = R5 = x
	; MOV R5, #0 ; R5 = x	
;findX
;	ADD R5, R5, #1 ; increment
;	MUL R6, R5, R5
;	CMP R6, R3
;	BLT findX ; keep incrementing until x^2 < R3

	SUB R7, R6, R3 ; R7 = y^2 = x^2 - N
	
	; now we know initial values of "x" and "y^2"
	; increment x and change y^2 until y^2 is a square
	; check whether y^2 is a square
checkSquare
	PUSH {LR}
	BL isYSquare ; if yes, R0 = 1, if no, 0
	POP {LR}
	CMP R0, #1
	BEQ calculateY
	ADD R5, R5, #1 ; x++
	MUL R6, R5, R5
	SUB R7, R6, R3 ; y^2 = x*x - N
	B checkSquare
	
	; once y^2 is a perfect square, use y to compute f1 and f2
	; (first compute sqrt(y^2))
	
	; put result into R0
isYSquare ; assume y^2 is in R7
	PUSH {LR} ; this value of LR is the next instruction in the startup file
	VMOV.F32 S0, R7 ; copy integer representation into FP reg
	VCVT.F32.S32 S0, S0 ; convert int to float
	
	MRS R8, FPSCR
	AND R8, #0xffbfffff ; floor mode
	ORR R8, #0x00800000
	MSR FPSCR, R8
	
	VSQRT.F32 S1, S0
	VCVTR.S32.F32 S1, S1
	
	; change Rmode to ceiling
	MRS R8, FPSCR
	AND R8, #0xff7fffff
	ORR R8, #0x00400000
	MSR FPSCR, R8
	
	VSQRT.F32 S2, S0
	VCVTR.S32.F32 S2, S2
	VMOV.F32 R8, S1
	VMOV.F32 R9, S2
	CMP R8,R9
	
	MOVEQ R0, #1
	MOVNE R0, #0
	POP {PC} ; this makes the next instruction to execute the instruction we linked from

calculateY
	VMOV.F32 S0, R7 ; copy integer representation into FP reg
	VCVT.F32.S32 S0, S0 ; convert int to float
	VSQRT.F32 S0, S0
	VCVT.S32.F32 S0, S0 ; convert float to int
	VMOV.F32 R8, S0 ; now R8 contains y
computeFactors
	ADD R1, R5, R8 ; f1 = x+y
	SUB R2, R5, R8 ; f2 = x-y

branchBack
	; PUSH {R3, R1, R2}
	MOV R0, R1 ; needed for 2 factors in one 64 bit number
	MOV R1, R2 ; 
	POP {R4-R12}
	BX LR
	END