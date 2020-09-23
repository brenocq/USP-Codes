		ORG 0
		SJMP	PROG
		ORG 3
		SJMP	EXTERN_0
		ORG 0Bh
		SJMP	TIMER_0
;--------------------------------
PROG:
ESTADO		EQU	20h
		; Interrupcao
		SETB	EA ; Habilita interrupcoes
		SETB	EX0 ; Habilita interrrupcao do extern 0
		SETB	ET0 ; Habilita interrupcao do timer 0
		SETB	IT0 ; Interrupcao externa em borda de descida
		; Timer
		MOV	TMOD, #00000101b ; Configura o timer (contador modo 1)
		MOV 	TH0, #0FFh
		MOV 	TL0, #0FBh
		MOV	ESTADO, #0 ; Estado inicial
		SETB 	TR0 ; Liga o T0

		SJMP	$

EXTERN_0:
		CLR 	EA ; Desabilita interrupcoes
		MOV	ESTADO, #0
		; Desliga leds
		SETB	P2.0
		SETB	P2.1
		SETB	P2.2
		MOV 	TL0, #0FBh; Ligar led apos 5 pulsos
		SETB 	EA ; Habilita interrupcoes novamente
		RETI

TIMER_0:	CLR 	EA ; Desabilita interrupcoes
		MOV 	TH0, #0FFh
		MOV	A, ESTADO
		CJNE	A, #0, ESTADO_UM
ESTADO_ZERO:	CLR	P2.0; Liga led 0
		MOV	ESTADO, #1; Muda o estado
		MOV 	TL0, #0F6h; Contar 10 para proximo led
		SJMP TIMER_0_END
ESTADO_UM:	CJNE	A, #1, ESTADO_DOIS
		CLR	P2.1; Liga led 1
		MOV	ESTADO, #2; Muda o estado
		MOV 	TL0, #0ECh; Contar 20 para proximo led
		SJMP TIMER_0_END
ESTADO_DOIS:	CJNE	A, #2, TIMER_0_END
		CLR	P2.2; Liga led 3
		MOV	ESTADO, #3; Muda o estado
TIMER_0_END:	SETB 	EA ; Habilita interrupcoes novamente
		RETI
		END
