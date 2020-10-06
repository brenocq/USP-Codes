		ORG 0h
		SJMP	PROG
		ORG 3h
		SJMP	EXTERN_0
		ORG 13h
		SJMP	EXTERN_1
;------------------------------------------------------------------
PROG:
COUNTING	EQU	20h.0
		; Interrupcoes
		SETB	EA ; Habilita interrupcoes
		SETB	EX0 ; Habilita interrupcao do extern 0
		SETB	EX1 ; Habilita interrupcao do extern 1
		MOV 	TCON, #00000101b ; Configura interrupcoes em borda de descida

LOOP:		JNB	COUNTING, LOOP ; Checa nao foi pausado
		CJNE  	A, #99h, SUM ; Checa deve zerar ou somar
		MOV	A, #0
		SJMP 	CONTINUE
SUM:		ADD	A, #1
		DA	A
CONTINUE:	CALL 	SHOW; Atualiza os leds
		CALL 	DELAY; Delay 100us
		SJMP 	LOOP

;------------------------------------------------------------------
SHOW:		MOV	B,A
		CPL	A
		MOV P2, A
		MOV	A,B
		RET

;------------------------------------------------------------------
DELAY:		MOV	R0, #031h; 100us
		NOP
		DJNZ	R0, $
		RET

;------------------------------------------------------------------
EXTERN_0:	SETB	COUNTING
		RETI
;------------------------------------------------------------------
EXTERN_1:	CLR	COUNTING
		RETI
;------------------------------------------------------------------
		END

