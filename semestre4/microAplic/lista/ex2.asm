		ORG 0h
		SJMP	PROG
		ORG 3h
		SJMP	EXTERN_0
		ORG 0Bh
		SJMP	TIMER_0
		ORG 13h
		SJMP	EXTERN_1
;------------------------------------------------------------------
PROG:
		; Interrupcoes
		SETB	EA ; Habilita interrupcoes
		SETB	ET0 ; Habilita interrupcao do timer 0
		SETB	EX0 ; Habilita interrupcao do extern 0
		SETB	EX1 ; Habilita interrupcao do extern 1
		SETB	PX0 ; Extern 0 com alta prioridade
		SETB	PX1 ; Extern 1 com alta prioridade
		MOV 	TCON, #00000101b ; Configura interrupcoes em borda de descida
		; Timer
		MOV	TMOD, #00000001b ; Configura o timer (modo 1) e 50us
		MOV 	TH0, #0FFh
		MOV 	TL0, #9Bh
		SETB 	TR0 ; Dispara o T0

		SJMP $

;------------------------------------------------------------------
EXTERN_0:	CLR 	EA ; Desabilita interrupcoes
		MOV	DPTR,#4000H
		MOVX	A,@DPTR
		MOV	DPTR,#4200H
		MOVX	@DPTR,A
		SETB	EA ; Habilita interrupcoes
		RETI
;------------------------------------------------------------------
EXTERN_1:	CLR 	EA ; Desabilita interrupcoes
		MOV	DPTR,#4200H
		MOVX	A,@DPTR
		MOV	P1,A
		SETB	EA ; Habilita interrupcoes
		RETI
;------------------------------------------------------------------
TIMER_0:	MOV 	TH0, #0FFh
		MOV 	TL0, #9Bh

		MOV	A,P2
		MOV	DPTR,#4000H
		MOVX	@DPTR,A

		RETI
		END
