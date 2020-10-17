		ORG 	0h
		SJMP	PROG
		ORG	3h
		SJMP	EXTERN_0
;--------------------------------------------
PROG:		SETB 	EA ; Habilita interrupções
		SETB 	EX0 ; Habilita a interrupção zero
		SETB 	IT0 ; Ativado em borda de descida (Alguma moeda foi detectada)

LOOP:		; Limpa saidas de controle
		CLR	P2.0
		CLR	P2.1
		CLR	P2.2
		; Confere quanto ja foi inserito
		CJNE  R0,#20,NOTEQUAL_20

		; Exatamente 20 foi inserido
		SETB	P2.0 ; Fornece o doce
		MOV	R0,#0 ; Remove 20 do total
		CALL DELAY_10MS ; Delay para sinal ser lido
		SJMP	LOOP

NOTEQUAL_20:	JNC GREATER_20
		; Menos que 20 foi inserido
		SJMP	LOOP ; Continua

GREATER_20:	; Mais que 20 foi inserido
		SETB	P2.0 ; Fornece o doce
		; Remove 20 do total
		MOV	A,R0
		SUBB	A,#20
		MOV	R0,A
;---------------- Calcula o troco --------------;
		CJNE  R0,#10,NOTEQUAL_10
		; Exatamente 10 de troco
		SETB	P2.2 ; Devolve 10 centavos
		MOV	R0,#0 ; Remove 10 do total
		CALL DELAY_10MS ; Delay para sinal ser lido
		SJMP	LOOP

NOTEQUAL_10:	JNC GREATER_10
		; Menos que 10 de troco (5 de troco)
		SETB	P2.1 ; Devolve 5 centavos
		MOV	R0,#0 ; Remove 5 do total
		CALL DELAY_10MS ; Delay para sinal ser lido
		SJMP	LOOP

GREATER_10:	; Mais que 10 de troco (15 de troco)
		SETB	P2.1 ; Devolve 5 centavos
		SETB	P2.2 ; Devolve 10 centavos
		MOV	R0,#0 ; Remove 15 do total
		CALL DELAY_10MS ; Delay para sinal ser lido
		SJMP	LOOP

;--------------------------------------------
EXTERN_0:	; Alguma moeda foi inserida
		CLR EA ; Desabilita interrupcoes
		JB	P1.0, NADA
		JB	P1.1, MOEDA_5
		JB	P1.2, MOEDA_10

MOEDA_20:	MOV	A,R0
		ADD	A,#20
		MOV	R0,A
		SETB EA ; Habilita interrupcoes
		RETI

MOEDA_10:	MOV	A,R0
		ADD	A,#10
		MOV	R0,A
		SETB EA ; Habilita interrupcoes
		RETI

MOEDA_5:	MOV	A,R0
		ADD	A,#5
		MOV	R0,A
NADA:		SETB EA ; Habilita interrupcoes
		RETI

;---------------------------------------------
DELAY_10MS:	; Comentado para facilitar os testes
		;MOV	R6, #015h
		;MOV	R7, #0ECh
		;NOP
		;DJNZ	R7, $
		;DJNZ	R6, $-5
		NOP
		NOP
		NOP
		RET