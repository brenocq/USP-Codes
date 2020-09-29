		; Configurando Comunicacao com 19200
		MOV 	PCON, #10000000b
		MOV 	TH1,#253
		MOV 	TL1,#253
		; Modo 2 de comunicacao
		SETB 	TR1
		MOV 	SCON,#10000000b
		SETB 	REN ; Habilita a Recepção
		
LOOP:		JNB 	RI,$ ;Espera terminar a recepção
		MOV 	A, SBUF ; Lê o dado recebido serialmente
		CLR 	RI ; Prepara para nova recepção

		CJNE  	A,#47H,CHECKY
		; Liga led P2.0
		CLR	P2.0
		SJMP 	LOOP
CHECKY:		CJNE  	A,#59H,CHECKR
		; Liga led P2.4
		CLR	P2.4
		SJMP 	LOOP
CHECKR:		CJNE  	A,#52H,CHECKD
		; Liga led P2.7
		CLR	P2.7
		SJMP 	LOOP
CHECKD:		CJNE  	A,#44H,LOOP
		; Desliga os leds
		SETB	P2.0
		SETB	P2.4
		SETB	P2.7
		SJMP 	LOOP
		END