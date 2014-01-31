	AREA text, CODE, READONLY
	IMPORT fermatAssem
	EXPORT fermatTestbench
fermatTestbench
	; for N = 1 to value in R5
	MOV R0, #0 ; R0 = N
	MOV R5, #9000
	
forLoop
	; f1, f2= myFunction(N) (R1 = f1, R2 = f2)
	ADD R0, #1 ; increment N
	MOV R8, R0 ; R8 also equals N
	PUSH {R8, LR, R5} ; push N, the original link address (back to the startup file), final value of N
	LDR R1, =fermatAssem
	BLX R1
	POP {R8, LR, R5} ; pop N, the original link address, final value of N
	MUL R4, R1, R0 ; R4 = f1 * f2
	CMP R8, R4 ; R0 contains f1, R1 contains f2
	BNE failure ; if N != f1*f2, the algorithm failed
	CMP R3, R5
	MOV R0, R8
	BNE forLoop ; if N != R5, loop
	B success
failure
	B failure
success
	BX LR
	END