		ORG 	0
		SJMP 	PROGRAM
;-------------------------------------------------
PROGRAM:
		ENAB 	EQU	P3.2
		RS 	EQU	P3.4
		RW 	EQU	P3.3
		D 	EQU	P2

		LCALL INIT_LCD
RECOMECA:	LCALL CLEAR_LCD
		MOV	A, #00h; Posicao do cursor no inicio
		LCALL 	POS_LCD

		;----------- Leitura primeiro numero ------------
LOOP_A:		CALL 	READ_KEYBOARD; Le valor do primeiro numero
		CJNE  	R0,#0FEH,CHECK_A; Checa se alguma tecla foi pressionada
		SJMP 	RECOMECA; Se FE, recomeca
CHECK_A:	JC 	VALID_NUMBER_A; Se numero, continua operacao
		SJMP 	LOOP_A; Se FF, nada foi pressionado, tenta novamente

VALID_NUMBER_A:	; Escreve o numero
		MOV	A, R0
		MOV	R1,A; Salva valor do primeiro numero 
		LCALL	WRITE_TEXT; Escreve numero no LCD
		; Escreve +
		MOV	A, #'+'
		LCALL	WRITE_TEXT; Escreve numero no LCD
		ACALL 	ESPERA_LIBERAR; Espera soltar a tecla
		
		;----------- Leitura segundo numero --------------
LOOP_B:		CALL 	READ_KEYBOARD; Le valor do segundo numero
		CJNE  	R0,#0FEH,CHECK_B; Checa se alguma tecla foi pressionada para B
		SJMP 	RECOMECA; Se FE, recomeca
CHECK_B:	JC 	VALID_NUMBER_B; Se numero, continua operacao
		SJMP 	LOOP_B; Se FF, nada foi pressionado, tenta novamente
VALID_NUMBER_B:	; Escreve o numero
		MOV	A, R0
		LCALL	WRITE_TEXT; Escreve numero no LCD
		; Escreve =
		MOV	A, #'='
		LCALL	WRITE_TEXT; Escreve numero no LCD

		; Mostra resultado
		ACALL 	MOSTRA_SOMA

		; Espera soltar a tecla
		ACALL 	ESPERA_LIBERAR

		; Espera ler uma letra para recomecar
ESPERA_RECOMECA:CALL 	READ_KEYBOARD
		CJNE  	R0,#0FEH,ESPERA_RECOMECA
		SJMP 	RECOMECA; Se FE, recomeca

;------------------------------------------------
MOSTRA_SOMA:	CLR 	C
		MOV	A, R0
		SUBB	A, #'0'; Converte ascii para numero
		ADD	A, R1
		SUBB	A, #'0'; Converte ascii para numero
		MOV	R0, A
		ACALL 	R0_TO_BCD
		; Converte MSB para ASCII
		MOV	A, R2
		ADD	A, #'0'
		; Escreve MSB
		LCALL	WRITE_TEXT; Escreve numero no LCD
		
		; Converte LSB para ASCII
		MOV	A, R1
		ADD	A, #'0'
		; Escreve LSB
		LCALL	WRITE_TEXT; Escreve numero no LCD
		RET

;---------------------------------
; Converte o valor de R0 para BCD
R0_TO_BCD:	; LSB -> R1
		; MSB -> R2
		MOV	A,R0

R3_CALCULATED:	MOV	R1,A
		; Converte para BCD
		CJNE	A,#00,TESTE
		;CPL	A
		; Se for zero, retorna zero
		MOV 	R1,#0
		MOV 	R2,#0
		MOV 	R3,#0
		RET

TESTE:		CLR	A ; Inicializa o contador BCD em zero
SHOW_LOOP:	ADD	A,#1 ; Incrementa o contador
		DA	A ; Ajuste do decimal do contador
		DJNZ	R1,SHOW_LOOP ; Decrementa o hexa ate zero

		; Processa R1
		MOV	R2,A
		ANL	A,#00001111b
		MOV	R1,A

		; Processa R2
		MOV	A,R2
		ANL	A,#11110000b
		SWAP	A
		MOV	R2,A
		
		RET
;------------------------------------------------
ESPERA_LIBERAR: ; Espera ate tecla ser liberada
		JNB	P1.0, WAIT_0
		JNB	P1.1, WAIT_1
		JNB	P1.2, WAIT_2
		JNB	P1.3, WAIT_3
		RET
WAIT_0:		JNB	P1.0, $
		RET
WAIT_1:		JNB	P1.1, $
		RET
WAIT_2:		JNB	P1.2, $
		RET
WAIT_3:		JNB	P1.3, $
		RET

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
AAAA:
BBBB:
CCCC:
DDDD:
ASTE:
HASH:		MOV	R0, #0FEh; FE para indicar que deve reiniciar
		RET
		END
