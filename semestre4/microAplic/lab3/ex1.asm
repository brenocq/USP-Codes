		ORG 0
LOOP:		CLR 	P2.0; Liga led 0
		SETB 	P2.1; Desliga led 1
		ACALL 	DELAY; Espera por 50 us
		SETB 	P2.0; Desliga led 0
		CLR 	P2.1; Liga led 1
		ACALL 	DELAY; Espera por 50 us
		SJMP 	LOOP

DELAY:
; START: Wait loop, time: 50 us
; Clock: 12000.0 kHz (12 / MC)
; Used registers: R4
		MOV	R4, #018h
		NOP
		DJNZ	R4, $
		RET
; Rest: 0
; END: Wait loop
		END