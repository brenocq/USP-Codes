		ORG 0
		SJMP	PROG
;--------------------------------------------
		ORG	3
		SJMP	EXTERNA_0
;--------------------------------------------
PROG:
XFLAG		EQU	20h.0
		CLR XFLAG ; Habilita para piscar em 10kHz

		SETB EX0 ; Habilita a interrupção zero
		SETB IT0 ; Ativado em descida de borda
		SETB PX0 ; Interrupção zero de alta prioridade
		SETB EA ; Habilita interrupções

LOOP:		CLR	P2.2; Liga o led
		ACALL	DELAY; Delay (10kHz ou 20kHz)
		SETB	P2.2; Desliga o led
		ACALL	DELAY; Delay (10kHz ou 20kHz)
		SJMP	LOOP
;--------------------------------------------
EXTERNA_0:
		CLR EA ; Desabilita interrupcoes para nao interromper
		JB XFLAG, EXTERNA_0_ST1; Vai para o estado atual

		; Estado zero
		SETB	XFLAG ; Habilita para piscar em 10kHz
		SETB EA ; Habilita interrupcoes novamente
		RETI
EXTERNA_0_ST1:	; Estado um
		CLR	XFLAG ; Limpa para piscar em 20kHz
		SETB EA ; Habilita interrupcoes novamente
		RETI
;--------------------------------------------
DELAY:		JB XFLAG, DELAY_20khz; Vai para o delay atual
; START: Wait loop, time: 100 us (10kHz)
		MOV	R4, #031h
		NOP
		DJNZ	R4, $
		RET

DELAY_20khz:
; START: Wait loop, time: 50 us (20kHz)
		MOV	R4, #018h
		NOP
		DJNZ	R4, $
		RET
		END


