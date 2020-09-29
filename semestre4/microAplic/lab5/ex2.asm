		ORG 0
FLAGX		EQU	30H 	; Flag de atendimento de interrupcao
		SJMP	PROG
		ORG	23H 	; Sub-rotina de interrupcao da Interrupcao Serial
		CLR	EA	; Desabilita interrupcao
		JNB	TI,FIM	; Verifica se foi recepcao
		CLR	TI	; Se for transmissao, limpa TI
		SJMP	FIM1
		
FIM:		MOV	A,SBUF	; Le o caractere da serial
		CLR	RI	; Se for recepcao, Limpa RI
		SETB	FLAGX	; Ativa flag de atendimento de interrupcao
		
FIM1:		SETB	EA 	; Re-abilita interrupcoes
		RETI		; Retorna

		; Configurando Comunicacao com 19200
PROG:		MOV 	PCON, #10000000b
		MOV 	TH1,#253
		MOV 	TL1,#253
		; Modo 2 de comunicacao
		SETB 	TR1
		MOV 	SCON,#10000000b
		; Configura Interrupcao serial
		SETB	EA	; Habilita interrupcoes
		SETB	IE.4	; Habilita interrupcao serial
		
		SETB 	REN ; Habilita a Recepção
LOOP:		
		CLR	FLAGX
		JNB	FLAGX,$ ; Espera caractere na serial ser recebido

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
