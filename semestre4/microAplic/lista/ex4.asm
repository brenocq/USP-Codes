		ORG 	0h
SENSOR_1	EQU	20h.0; Flag indicando se objeto foi detectado pelo sensor 1 (1 indica nenhum objeto)
SENSOR_2	EQU	20h.1; Flag indicando se objeto foi detectado pelo sensor 2 (1 indica nenhum objeto)
		SJMP	PROG
		ORG	3h
		SJMP	EXTERN_0
		ORG	13h
		SJMP	EXTERN_1
;--------------------------------------------
PROG:		SETB 	EA ; Habilita interrupções
		SETB 	EX0 ; Habilita a interrupção zero
		SETB 	IT0 ; Ativado em borda de descida (Objeto detectado pelo sensor 1)
		SETB 	EX1 ; Habilita a interrupção um
		SETB 	IT1 ; Ativado em borda de descida (Objeto detectado pelo sensor 2)

		; Limpa flag dos sensores
		SETB	SENSOR_1
		SETB	SENSOR_2

		; Acumulador para executar ciclo tres vezes
		MOV	A,#3

LOOP:		; Liga motor para baixar o objeto
		SETB	P2.7
		SETB	P2.6
		; Espera sensor 1 detectar o objeto
WAIT_S1_DETEC:	JB	SENSOR_1, WAIT_S1_DETEC
		SETB	SENSOR_1 ; Reseta flag de leitura
		CLR	P2.6 ; Para o motor
		SETB	P1.2 ; Liga aquecimento do forno
		CALL 	DELAY_500MS
		CLR	P1.2 ; Desliga aquecimento do forno
		CLR	P2.7 ; Inverte sentido do motor
		SETB	P2.6 ; Liga o motor
WAIT_S2_DETEC:	JB	SENSOR_2, WAIT_S2_DETEC
		SETB	SENSOR_2 ; Reseta flag de leitura
		CLR	P2.6 ; Desliga o motor
		SETB	P1.0 ; Aciona o resfriamento
		CALL 	DELAY_500MS
		DJNZ	A, LOOP ; Executa o ciclo 3 vezes
		SJMP	$ ; Apos tres vezes, nao faz nada

;--------------------------------------------
EXTERN_0:	CLR	SENSOR_1
		RETI

;--------------------------------------------
EXTERN_1:	CLR	SENSOR_2
		RETI

;---------------------------------------------
DELAY_500MS:	; b) Parametros de programacao do tempo envolvido:
		; R7 = 248
		; R6 = 250
		; R5 = 4

		; Comentado para facilitar os testes
		;MOV	R5, #004h
		;MOV	R6, #0FAh
		;MOV	R7, #0F8h
		;NOP
		;DJNZ	R7, $
		;DJNZ	R6, $-5
		;DJNZ	R5, $-9
		RET
