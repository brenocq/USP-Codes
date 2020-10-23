	ORG	0
	; Mapeando 32148709 para memoria externa
	; 32148709 -> 6h 12h 4Fh 4Ch 0h Fh 1h 4h
PROG:	MOV	DPTR,#8000H
	MOV	A, #4h; 9
	MOVX	@DPTR, A
	
	INC	DPTR
	MOV	A, #1h; 0
	MOVX	@DPTR, A
	
	INC	DPTR
	MOV	A, #0Fh; 7
	MOVX	@DPTR, A

	INC	DPTR
	MOV	A, #0h; 8
	MOVX	@DPTR, A

	INC	DPTR
	MOV	A, #4Ch; 4
	MOVX	@DPTR, A

	INC	DPTR
	MOV	A, #4Fh; 1
	MOVX	@DPTR, A

	INC	DPTR
	MOV	A, #12h; 2
	MOVX	@DPTR, A

	INC	DPTR
	MOV	A, #6h; 3
	MOVX	@DPTR, A
LOOP:	; Mostra valores no display a partir da memoria externa
	ACALL DMUX
	SJMP LOOP
;---------------------------------
DMUX:	
	MOV	B, #01
CONT:	ACALL	APAGA
	MOVX	A,@DPTR
	MOV	P1,A
	MOV	P2,B
	MOV	A, B
		A
	MOV	B, A
	INC	DPTR
	CJNE	A,#1h,CONT
	ACALL	APAGA
	RET
;---------------------------------
APAGA:	MOV	P1,#0FFh
	MOV	P2,#00h
	RET
	END