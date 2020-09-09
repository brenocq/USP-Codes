		ORG 	0
		MOV	DPTR,#TAB	; Aponta o ponteiro para o endereco TAB
		CLR 	A		; Zera o acumulador A
		MOVC 	A,@A+DPTR	; Le o dado no endereco TAB
		MOV	B, A		; Move do acumulador A para o B
		INC	DPTR		; Aponta o ponteiro para a proxima posicao (TAB+1)
		CLR	A		; Zera o acumulador A
		MOVC 	A,@A+DPTR	; Le o dado de TAB+1
		CJNE	A,B,DIFERENTE	; Compara A e B 
		MOV	R0, A		; Se forem iguais, Salva A
		SJMP	SALVAR		; Salva
DIFERENTE:	JC 	B_MAIOR		; Jump se B>A
		SJMP	SALVAR		; Salva
B_MAIOR:	MOV	A, B		; Move B para A
SALVAR:		MOV	DPTR,#1200H
		MOVX	@DPTR, A
		SJMP	$
TAB:		DB 	43H, 32H
		END