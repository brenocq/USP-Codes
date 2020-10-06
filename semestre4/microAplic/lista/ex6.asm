		ORG 0h
		SJMP	PROG
		ORG 3h
		SJMP	EXTERN_0
		ORG 0Bh
		SJMP	TIMER_0
		ORG 13h
		SJMP	EXTERN_1
		ORG 1Bh
		SJMP	TIMER_1
;------------------------------------------------------------------
PROG:
		; Interrupcoes
		SETB	EA ; Habilita interrupcoes
		SETB	EX0 ; Habilita interrupcao do extern 0
		SETB	ET0 ; Habilita interrupcao do timer 0
		SETB	EX1 ; Habilita interrupcao do extern 1
		SETB	ET1 ; Habilita interrupcao do timer 1
		SETB	PX0 ; Extern 0 com alta prioridade
		SETB	PT0 ; Timer 0 com alta prioridade
		MOV 	TCON, #00000101b ; Configura interrupcoes em borda de descida
		; Timer
		MOV	TMOD, #00010001b ; Configura o timer (modo 1) e 50us
		MOV 	TH0, #0D8h
		MOV 	TL0, #0EFh
		MOV 	TH1, #15h
		MOV 	TL1, #9Fh
		SETB 	TR0 ; Dispara o T0
		SETB 	TR1 ; Dispara o T1

		SJMP $

;------------------------------------------------------------------
EXTERN_0:	MOV	B, P1
		MOV	DPTR,#5000H
		MOVX	A,@DPTR
		MOV	P1, A
		MOV	A, B
		MOVX	@DPTR,A
		RETI
;------------------------------------------------------------------
EXTERN_1:	MOV	DPTR,#5000H
		MOVX	A,@DPTR
		MOV	7Fh, A
		RETI
;------------------------------------------------------------------
TIMER_0:	MOV 	TH0, #0D8h
		MOV 	TL0, #0EFh

		MOV	A, 7Fh
		MOV	DPTR,#5200H
		MOVX	@DPTR, A

		RETI

;------------------------------------------------------------------
TIMER_1:	MOV 	TH1, #15h
		MOV 	TL1, #9Fh

		MOV	DPTR,#5200H
		MOVX	A,@DPTR
		MOV	DPTR,#5000H
		MOVX	@DPTR,A

		RETI
		END
