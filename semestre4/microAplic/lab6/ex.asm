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
		MOV	A, #0
		
LOOP:		JNB	COUNTING, LOOP ; Checa nao foi pausado
		CJNE  	A, #99, SUM ; Checa deve zerar ou somar
		MOV	A, #0
		SJMP 	CONTINUE
SUM:		ADD	A, #1
CONTINUE:	CALL 	SHOW; Atualiza os leds
		;CALL 	DELAY; Delay 100us
		SJMP 	LOOP

;------------------------------------------------------------------
SHOW:		MOV	R0,A
		MOV	R1,A

		CJNE	A,#00,TESTE
ZERO:		CPL	A
		MOV 	P2, A; Se for zero, mostra zero
		MOV	A, R1 ; Retorna o contador para o valor salvo
		RET

TESTE:		CLR	A ; Inicializa o contador BCD em zero
SHOW_LOOP:	ADD	A,#1 ; Incrementa o contador
		DA	A ; Ajuste do decimal do contador
		DJNZ	R0,SHOW_LOOP ; Decrementa o hexa ate zero
		CPL	A
		MOV P2, A ; Mostra o contador BCP

		MOV	A, R1 ; Retorna o contador para o valor salvo
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


