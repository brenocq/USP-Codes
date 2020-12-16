		ORG 	0
		SJMP	PROGRAM
;--------------------------------------------
PROGRAM:
		; LCD info
RS 		EQU	P3.4
RW 		EQU	P3.3
ENAB 		EQU	P3.2
D 		EQU	P2
		; SENSOR info
DQ 		EQU	P3.0
CLK 		EQU	P3.1
RST 		EQU	P1.0

		;------------- Inicializa Display -------------
		LCALL 	INIT_LCD
		LCALL 	CLEAR_LCD
		MOV	A, #00h; Posicao do cursor no inicio
		LCALL 	POS_LCD

		;------------- Inicializa DS1620 -------------
		ACALL	CONF_SENSOR

		; Imprime TEMPERATURA
		ACALL	PRINT_TEMP

LOOP:
		ACALL	PRINT_VALUE
		SJMP 	LOOP

PRINT_VALUE:	; Pula para inicio da segunda linha
		MOV	A, #40h
		LCALL 	POS_LCD

		; Le o sensor e salva no R1 e R0
		ACALL	LE_SENSOR

		;------------ Imprime sinal --------------
		MOV	A,R1
		CJNE	A,#0,NEG_VALUE
		; Shift R0 e salva em R2
		MOV	A, R0
		RRC	A
		MOV	R2,A
		; Imprime +
		MOV	A, #'+'
		LCALL	WRITE_TEXT; Escreve no LCD
		SJMP	END_SIG_VALUE
NEG_VALUE:
		; Complemento de 2 de R0 em R2
		MOV	A, R0
		RRC	A
		CPL	A
		ANL	A, #01111111b
		ADD	A, #1
		MOV	R2,A
		; Imprime -
		MOV	A, #'-'
		LCALL	WRITE_TEXT; Escreve no LCD
END_SIG_VALUE:
		;------------- Imprime valor --------------
		MOV	A, R2; R2 armazena R0 ja com complemento de 2 se for negativo
		ACALL	CONVERT_BCD; Transforma para BCD em R7,R6,R5

		MOV	A, R7; MSD
		ADD	A, #'0'
		LCALL	WRITE_TEXT; Escreve no LCD
		MOV	A, R6; Middle
		ADD	A, #'0'
		LCALL	WRITE_TEXT; Escreve no LCD
		MOV	A, R5; LSB
		ADD	A, #'0'
		LCALL	WRITE_TEXT; Escreve no LCD

		;--------------- Ponto ----------------
		MOV	A, #'.'
		LCALL	WRITE_TEXT; Escreve no LCD

		;---------- Imprime decimal -----------
		; (no simulador sempre 0)
		MOV	A, R0
		ANL	A, #00000001b

		CJNE	A,#0,DEC_5
		MOV	A, #'0'
		LCALL	WRITE_TEXT; Escreve no LCD
		SJMP	END_DEC_VALUE

DEC_5:		MOV	A, #'5'
		LCALL	WRITE_TEXT; Escreve no LCD
END_DEC_VALUE:

		;----------- Imprime celcius ----------
		MOV	A, #0DFh
		LCALL	WRITE_TEXT; Escreve no LCD
		MOV	A, #'C'
		LCALL	WRITE_TEXT; Escreve no LCD

		RET
;-----------------------------
PRINT_TEMP:
		MOV	A, #'P'
		MOV	R0, #11; Numero de caracteres na string
PRT_TMP_CONT:	MOV	A, #11
		CLR 	C
		SUBB	A,R0
		ADD	A,#6
		MOVC	A,@A+PC
		LCALL	WRITE_TEXT; Escreve no LCD
		DJNZ	R0, PRT_TMP_CONT
		RET
TAB:		DB 	'TEMPERATURA'
;--------------------------------
CONVERT_BCD:	; Convert A to BCD R7 R6 R5
		; R7->MSB
		; R6->Middle
		; R5->LSB
		MOV	B,#10
		DIV	AB      ; floor(number / 10) in A, 1s in B
		MOV	R5,B    ; 1s are now in R1 (bits 3 to 0)
		MOV	B,#10
		DIV	AB      ; floor(number / 100) in A, 10s in B
		MOV	R7,A    ; 100s are now in R0 (bits 3 to 0)
		MOV	R6,B
		RET
;----------------------------------------------
;-------------- SUB-ROTINAS SENSOR ------------
;----------------------------------------------
CONF_SENSOR:; Configura sensor DS1620
		MOV 	A,#0AH ;Configuração = cpu & Continuo
		ACALL 	OUT_CMD
		MOV 	A,#0EEH ;Iniciar conversão.
		ACALL 	OUT_CMD
		RET
;-------------------------------------------
LE_SENSOR:; Lê a temperatura do sensor DS1620 e salva em R0 = LSB
;      R1 = 0(se positivo), R1=1(se negativo))
		MOV A,#0AAH ; Comando de leitura de
		ACALL OUT_CMD ;temperatura (9 bits).
		ACALL IN_DATA ; Ler o LSB (8 bits)da temperatura.
		MOV R0,A ;Salvar o LSB em R0.
		MOV 20H.0,C ; Ler o Bit de sinal (nono
		;bit) da temperatura
		MOV R1,20H ; Salvar no bit 0 de
		;R1 (1 = negativo 0 = positivo)
		MOV A,#0EEH ; Iniciar outra conversão.
		ACALL OUT_CMD
		RET
;-------------------------------------------
IN_DATA:; Lê um dado do DS1620.
		CLR A
		SETB DQ ; DQ será usado como
		;entrada (leitura)
		SETB RST
		MOV R7,#9
SERIAL2: 	SETB CLK
		CLR CLK
		MOV C,DQ
		SETB CLK
		RRC A
		DJNZ R7,SERIAL2
		RLC A
		RET
;---------------------------------------
OUT_CMD:; Envia comando para o DS1620
		CLR 	RST ; É necessário pulsar o Reset antes de enviar comando
		SETB 	RST
		MOV 	R7,#8
SERIAL: 	RRC 	A ;Desloca o ACC para enviar o cada bit (LSB) via Carry
		MOV 	DQ,C ; Envia bit a bit para DQ
		ACALL 	PULSE ; Pulsa o clock a cada bit enviado
		DJNZ 	R7,SERIAL
		RET
;---------------------------------------
PULSE:; Envia um pulso para o pino de clock do DS1620
		SETB 	CLK
		CLR 	CLK
		SETB 	CLK
		RET
;------------------------------------------
;-------------- SUB-ROTINAS LCD -----------
;------------------------------------------
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
		;JB	D.7, $ (DESABILITADO)

		CLR	ENAB
		CLR	RW
		RET
		END