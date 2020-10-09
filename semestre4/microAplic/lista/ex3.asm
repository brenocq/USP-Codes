		ORG 0h
		SJMP	PROG
		ORG 3h
		SJMP	EXTERN_0
		ORG 13h
		SJMP	EXTERN_1
;------------------------------------------------------------------
PROG:
		; Interrupcoes
		SETB	EA ; Habilita interrupcoes
		SETB	EX0 ; Habilita interrupcao do extern 0
		SETB	EX1 ; Habilita interrupcao do extern 1
		MOV 	TCON, #00000101b ; Configura interrupcoes em borda de descida

		SETB	P1.1 ; Liga valvula V2 que enche

		SJMP $

;------------------------------------------------------------------
EXTERN_0:	CLR 	EA ; Desabilita interrupcoes

		; Nivel de agua descendo, volta a encher
		CLR	P1.0 ; Desliga valvula V1 que drena
		SETB	P1.1 ; Liga valvula V2 que enche

		SETB	EA ; Habilita interrupcoes
		RETI
;------------------------------------------------------------------
EXTERN_1:	CLR 	EA ; Desabilita interrupcoes

		; Reservatorio muito cheio, comeca a drenar
		SETB	P1.0  ; Liga valvula V1 que drena
		CLR	P1.1 ; Desliga valvula V2 que enche

		SETB	EA ; Habilita interrupcoes
		RETI
		END