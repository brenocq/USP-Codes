		ORG 0
		SJMP	PROG
		ORG 3
		SJMP	EXTERN_0
		ORG 0Bh
		SJMP	TIMER_0
;--------------------------------
PROG:
CLK_FLAG	EQU	20h.0
NIVEL_FLAG	EQU	20h.1
		; Interrupcao
		SETB	EA ; Habilita interrupcoes
		SETB	EX0 ; Habilita interrrupcao do extern 0
		SETB	ET0 ; Habilita interrupcao do timer 0
		SETB	IT0 ; Interrupcao externa em borda de descida
		; Timer
		;CLR	G0 ; Controle por software
		;CLR	CT0 ; Definir como temporizador
		;SETB	M10 ; Modo
		;CLR	M00 ; Modo
		MOV	TMOD, #00000010b ; Configura o timer (auto-recarregavel)
		MOV 	TH0, #0E6h
		MOV 	TL0, #0E6h
		SETB 	TR0 ; Liga o T0

		SJMP	$

EXTERN_0:
		CLR 	EA ; Desabilita interrupcoes
		JB 	CLK_FLAG, EXTERN_0_ST1; Vai para o estado atual
		; Muda para 10kHz
		SETB	CLK_FLAG ; Muda para piscar em 10kHz
		MOV 	TH0,#0CDh
		SETB 	EA ; Habilita interrupcoes novamente
		RETI
EXTERN_0_ST1:	; Muda para 20kHz
		CLR	CLK_FLAG ; Muda para piscar em 20kHz
		MOV 	TH0,#0E6h
		SETB 	EA ; Habilita interrupcoes novamente
		RETI

TIMER_0:	CLR 	EA ; Desabilita interrupcoes
		JB	NIVEL_FLAG, TIMER_TO_BAIXO; Confere se muda para subida ou descida
		; Muda para nivel alto
		SETB	NIVEL_FLAG ; Nivel alto
		SETB	P2.0
		SETB 	EA ; Habilita interrupcoes novamente
		RETI
TIMER_TO_BAIXO: ; Muda para nivel baixo
		CLR	NIVEL_FLAG ; Nivel baixo
		CLR	P2.0
		SETB 	EA ; Habilita interrupcoes novamente
		RETI
		END