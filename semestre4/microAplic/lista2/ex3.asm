		ORG 	0
		SJMP 	PROGRAM
;--------------------------------------------
		ORG 	0Bh
		CPL	P3.6
		RETI
;--------------------------------------------
		ORG 	13h
		SJMP	EXTERN_1
;--------------------------------------------
		ORG 	23h
		SJMP	SERIAL
;--------------------------------------------
PROGRAM:
EO		EQU	P3.7
ADC_DATA	EQU	P0
IN_Y		EQU	R0
FLAG_S		EQU	30h; Flag de atendimento a serial
		;--------- Interrupcao
		SETB 	EA ; Habilita interrupções
		SETB 	EX1 ; Habilita a interrupção um
		SETB 	IT1 ; Interrupção em borda de descida

		;--------- Timer
		SETB	ET0; Habilita timer 0
		MOV	TH0, #0CDh; Timer para 50us (50us nivel alto, 50us nivel baixo -> 100us de periodo)
		MOV	TL0, #0CDh
		MOV	TMOD, #00100010b; Timer 0 e 1 no modo 2
		SETB	TR0; Inicializa timer 0

		;--------- Serial
		SETB	IE.4; Habilita interrupcao serial
		; Configurando Comunicacao com 9600
		MOV 	PCON, #10000000b
		MOV 	TH1,#250
		MOV 	TL1,#250
		; Modo 2 de comunicacao
		SETB 	TR1
		MOV 	SCON,#1000000b
		SETB 	REN ; Habilita a Recepção

		; Seleciona ADC ao inves da RAM
		CLR	P2.0;---------- Seleciona porta analogica
		MOV	IN_Y, #0; Define Y como 0

LOOP:		MOV	A, IN_Y
		MOVX	@DPTR, A

		;---------- Envia string pela serial (como demora para transmitir os dados lidos ja estarao atualizados)
		ACALL 	SEND_STRING

		;---------- Increementa Y
		MOV	A, IN_Y
		CJNE  	A,#7h, NOT_MAX_Y
		MOV	IN_Y, #0; Volta y para 0
		SJMP 	LOOP
NOT_MAX_Y:	ADD	A,#1 ; Incrementa y
		MOV	IN_Y,A
		SJMP 	LOOP
;----------------------------
EXTERN_1:	; READ ANALOG (Atualiza R1 com tensao lida)
		CLR	EA; Desabilita interrupcoes
		CLR	EO; Enable output (negado pelo OR NOT)
		MOV	A, ADC_DATA
		SETB	EO
		MOV	B, #23
		DIV	AB
		; Se igual a 11, define como 10
		CJNE  	A,#11, EXTERN_END
		MOV	A, #10
EXTERN_END:	MOV	R1, A; Guarda o quociente (tensao lida)
		SETB	EA; Habilita interrupcoes novamente
		RETI
;----------------------------
SERIAL:
		CLR 	EA; Desabilita interrupcoes
		JNB	TI,SERIAL_REC; Verifica se foi recepcao
		CLR	TI; Se foi transmissao, Limpa TI
		SJMP 	SERIAL_FIM
SERIAL_REC:	CLR	RI; Limpa RI
SERIAL_FIM:	SETB	EA; Habilita interrupcoes
		SETB	FLAG_S
		RETI
;---------------------------- TRANSMITE A STRING PELA SERIAL
SEND_STRING:	CLR	FLAG_S

		; Transmite 'VALOR ANALOGICO DA TENSAO NO SENSOR '
		ACALL 	SEND_START

		; Transmite y
		MOV	A, IN_Y
		ADD	A,#'0'
		MOV 	SBUF, A
		CLR	FLAG_S
		JNB	FLAG_S, $

		; Transmite ' = '
		ACALL 	SEND_MIDDLE

		; Transmite xx (valor lido pelo adc)
		MOV	A, R1
		CJNE  	A,#0Ah, NOTEQUAL
		;---------- Transmite 10
		MOV	A,#'1'
		MOV 	SBUF, A
		CLR	FLAG_S
		JNB	FLAG_S, $

		MOV	A,#'0'
		MOV 	SBUF, A
		CLR	FLAG_S
		JNB	FLAG_S, $
		SJMP	SEND_FINISH
NOTEQUAL:	;----------- Transmite valor menor que 10
		MOV	A,#'0'
		MOV 	SBUF, A
		CLR	FLAG_S
		JNB	FLAG_S, $
		
		ADD	A, R1
		MOV 	SBUF, A
		CLR	FLAG_S
		JNB	FLAG_S, $

		; Transmite ' volts'
SEND_FINISH:	ACALL 	SEND_END
		RET
;------------------------------------ AUX TRANSMITIR INICIO
SEND_START:
		MOV	R0, #36;36; Numero de caracteres na string
SEND_S_PRINT:	MOV	A, #36
		CLR 	C
		SUBB	A,R0
		ADD	A,#10
		MOVC	A,@A+PC
		MOV 	SBUF, A
		CLR	FLAG_S
		JNB	FLAG_S, $
		DJNZ	R0, SEND_S_PRINT
		RET
TAB:		DB 	'VALOR ANALOGICO DA TENSAO NO SENSOR '
;------------------------------------ AUX TRANSMITIR MEIO
SEND_MIDDLE:
		MOV	R0, #3;36; Numero de caracteres na string
SEND_M_PRINT:	MOV	A, #3
		CLR 	C
		SUBB	A,R0
		ADD	A,#10
		MOVC	A,@A+PC
		MOV 	SBUF, A
		CLR	FLAG_S
		JNB	FLAG_S, $
		DJNZ	R0, SEND_M_PRINT
		RET
		DB ' = '
;------------------------------------ AUX TRANSMITIR FINAL
SEND_END:
		MOV	R0, #6;36; Numero de caracteres na string
SEND_E_PRINT:	MOV	A, #6
		CLR 	C
		SUBB	A,R0
		ADD	A,#10
		MOVC	A,@A+PC
		MOV 	SBUF, A
		CLR	FLAG_S
		JNB	FLAG_S, $
		DJNZ	R0, SEND_E_PRINT
		RET
		DB ' volts'

		END
