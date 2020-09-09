		ORG 	0
		MOV	DPTR,#1200H		; Aponta o DPTR para #1200H
LOOP:		JB 	P1.0, P1_UM		; Verificando se P1.0 está com 1
		MOV	A, #0FFH		; Move #0FFH para o acumulador
		MOVX	@DPTR, A		; Escreve do acumulador para memoria externa
		SETB 	P3.0			; Seta o P3.0
		CLR 	P3.1			; Zera o P3.1
		SJMP	LOOP			; Volta para o loop
P1_UM:		MOV	A, #7FH			; Move #7FH para o acumulador
		MOVX	@DPTR, A		; Escreve do acumulador para memoria externa
		SETB 	P3.1			; Seta o P3.1
		CLR 	P3.0			; Zera o P3.0
		SJMP	LOOP			; Volta para o loop
		END
