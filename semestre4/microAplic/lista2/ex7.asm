; Chamar esta sub-rotina ao parar a bomba,
; ou seja, apos todos os CLR BOMBA (EXTERN_1 e TIMER_1)

; Deve ser configurado a serial no ex6
; Deve ser criada uma flag FLAG_S para atender a serial
; Deve ser criada uma sub-rotina de atendimento a interrupcao serial

VALIDAR_TRANSACAO:
		CLR	EA; Desabilita interrupcoes
		; Dado que o numero ja esta convertido (R7, R6, R5)
		; Transmitir caracteres ascii pela serial

		; Converte e transmite MSB
		MOV	A, R7
		ADD	A, #'0'
		MOV 	SBUF, A
		CLR	FLAG_S
		JNB	FLAG_S, $

		; Converte e transmite Middle
		MOV	A, R6
		ADD	A, #'0'
		MOV 	SBUF, A
		CLR	FLAG_S
		JNB	FLAG_S, $

		; Converte e transmite LSB
		MOV	A, R5
		ADD	A, #'0'
		MOV 	SBUF, A
		CLR	FLAG_S
		JNB	FLAG_S, $

NAO_OK:		; Espera resposta de OK
		CLR	FLAG_S
		JNB	FLAG_S, $; Esperar ler entrada serial em A
		CJNE	A, #3Ch, NAO_OK

		; Transacao OK, retransmite para P0
		MOV	P0, A

		; Continua programa, bomba liberada
		SETB	EA; Habilita interrupcoes
		RET