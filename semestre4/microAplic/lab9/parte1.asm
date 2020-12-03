		ORG 	0
		SJMP 	PROGRAM
;-------------------------------------------------
PROGRAM:
		ENAB 	EQU	P3.2
		RS 	EQU	P3.4
		RW 	EQU	P3.3
		D 	EQU	P2
		FLAGW	EQU	20h.0; Flag de espera

		LCALL INIT_LCD
		LCALL CLEAR_LCD
		MOV	A, #00h; Posicao do cursor no inicio
		LCALL 	POS_LCD

LOOP:		CALL 	READ_KEYBOARD; Le valor do teclado
		CJNE  R0,#0FFH,VALID_NUMBER; Checa se alguma tecla foi pressionada
		SJMP 	LOOP

VALID_NUMBER:	MOV	A, R0
		LCALL	WRITE_TEXT; Escreve letra no LCD
		; Espera ate tecla ser liberada
		JNB	P1.0, WAIT_0
		JNB	P1.1, WAIT_1
		JNB	P1.2, WAIT_2
		JNB	P1.3, WAIT_3
		SJMP 	LOOP
WAIT_0:		JNB	P1.0, $
		SJMP	LOOP
WAIT_1:		JNB	P1.1, $
		SJMP	LOOP
WAIT_2:		JNB	P1.2, $
		SJMP	LOOP
WAIT_3:		JNB	P1.3, $
		SJMP	LOOP
		

;------------------------------------------------- Funções do LCD
INIT_LCD:	CLR	RW
		SETB	ENAB
		CLR	RS
		MOV	D, #38h
		CLR	ENAB
		LCALL	WAIT_LCD
		;------
		SETB	ENAB
		CLR	RS
		MOV	D, #0Eh
		CLR	ENAB
		CALL	WAIT_LCD
		;------
		SETB	ENAB
		CLR	RS
		MOV	D, #06h
		CLR	ENAB
		LCALL	WAIT_LCD	
		RET
;-----------------
CLEAR_LCD:	CLR	RW
		SETB	ENAB
		CLR	RS
		MOV	D, #01h
		CLR	ENAB
		LCALL	WAIT_LCD
		RET
;-----------------
POS_LCD:	CLR	RW
		SETB	ENAB
		CLR	RS
		ADD	A, #80h
		MOV	D, A
		CLR	ENAB
		LCALL	WAIT_LCD
		RET
;-----------------
WRITE_TEXT:	CLR	RW
		SETB	ENAB
		SETB	RS
		MOV	D, A
		CLR	ENAB
		LCALL	WAIT_LCD
		RET
;-----------------
WAIT_LCD:	SETB	RW
		SETB	ENAB
		CLR	RS
		MOV	D, #0FFh
		;JB	D.7, $

		CLR	ENAB
		CLR	RW
		RET

;-------------------------------------------------
READ_KEYBOARD:	MOV 	P1,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P1.4 ; Zera coluna 1,4,7,*
		JNB	P1.0, UM
		JNB	P1.1, QUATRO
		JNB	P1.2, SETE
		JNB	P1.3, ASTE

		MOV 	P1,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P1.5 ; Zera coluna 2,5,8,0
		JNB	P1.0, DOIS
		JNB	P1.1, CINCO
		JNB	P1.2, OITO
		JNB	P1.3, ZERO

		MOV 	P1,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P1.6 ; Zera coluna 3,6,9,#
		JNB	P1.0, TRES
		JNB	P1.1, SEIS
		JNB	P1.2, NOVE
		JNB	P1.3, HASH

		MOV 	P1,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P1.7 ; Zera coluna A,B,C,D
		JNB	P1.0, AAAA
		JNB	P1.1, BBBB
		JNB	P1.2, CCCC
		JNB	P1.3, DDDD

		MOV	R0, #0FFh; Se nao pressionar nada, retorna FF
		RET

ZERO:		MOV R0, #'0'
		RET
UM:		MOV R0, #'1'
		RET
DOIS:		MOV R0, #'2'
		RET
TRES:		MOV R0, #'3'
		RET
QUATRO:		MOV R0, #'4'
		RET
CINCO:		MOV R0, #'5'
		RET
SEIS:		MOV R0, #'6'
		RET
SETE:		MOV R0, #'7'
		RET
OITO:		MOV R0, #'8'
		RET
NOVE:		MOV R0, #'9'
		RET
AAAA:		MOV R0, #'A'
		RET
BBBB:		MOV R0, #'B'
		RET
CCCC:		MOV R0, #'C'
		RET
DDDD:		MOV R0, #'D'
		RET
ASTE:		MOV R0, #'E'
		RET
HASH:		MOV R0, #'F'
		RET

		END