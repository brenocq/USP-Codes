		ORG 0
		SJMP	PROG
		ORG 0Bh
		SJMP	TIMER_0
;--------------------------------
PROG:
		; Timer
		MOV	TMOD, #00000001b ; Configura o timer (modo 1) e 50ms
		MOV 	TH0, #3Ch
		MOV 	TL0, #0AFh
		SETB	EA ; Habilita interrupcoes
		SETB	ET0 ; Habilita interrupcao do timer 0
		SETB 	TR0 ; Dispara o T0

		MOV	A, #0; Zera contador

LOOP:		CJNE  	A,#03H,LOOP; Loop enquanto acumulador menor que 100
		; Executa esta linha a cada 5 segundos
		MOV	A, #0
		SJMP LOOP

TIMER_0:	CLR 	EA ; Desabilita interrupcoes
		MOV 	TH0, #0FFh
		MOV 	TL0, #0CDh
		ADD	A, #1; Soma no counter a cada 50ms

		SETB	EA ; Habilita interrupcoes
		RETI
		END