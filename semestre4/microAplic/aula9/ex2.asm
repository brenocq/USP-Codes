		ORG	0

LOOP:		; 2 displays menos significativos
		MOV	DPTR,#1000H
		MOVX	A,@DPTR; Recebe o numero
		MOV	B,#1; Primeiro display
		ACALL	MOSTRA_DA_MEM

		; 2 displays seguintes
		MOV	A,B ; Incrementa a posicao
		RL	A
		MOV	B,A
		MOV	DPTR,#2000H
		MOVX	A,@DPTR; Recebe o numero
		ACALL	MOSTRA_DA_MEM

		; Proximos 2 displays
		MOV	A,B ; Incrementa a posicao
		RL	A
		MOV	B,A
		MOV	DPTR,#3000H
		MOVX	A,@DPTR; Recebe o numero
		ACALL	MOSTRA_DA_MEM

		; 2 displays mais significativos
		MOV	A,B ; Incrementa a posicao
		RL	A
		MOV	B,A
		MOV	DPTR,#4000H
		MOVX	A,@DPTR; Recebe o numero
		ACALL	MOSTRA_DA_MEM
		SJMP LOOP
		
MOSTRA_DA_MEM:	; Mostra da memoria em dois displays
		; INPUT: A->numero, B->posicao
		ACALL	A_TO_BCD
		MOV	R0,A
		; Mostra digito menos significativo
		ANL	A,#00001111b 
		MOV	P2, B
		ACALL	SHOW
		; Mostra digito mais significativo
		MOV	A,B
		RL	A
		MOV	B,A
		MOV	P2, B ; Proximo display
		MOV	P1,#0FFh 
		MOV	A,R0
		SWAP	A
		ANL	A,#00001111b ; Proximo numero para mostrar
		ACALL	SHOW
;---------------------------------
; Converte o valor em A para BCD
A_TO_BCD:	MOV	R0,A

		CJNE	A,#00,TESTE
ZERO:		;CPL	A
		; Se for zero, retorna zero zero
		RET

TESTE:		CLR	A ; Inicializa o contador BCD em zero
SHOW_LOOP:	ADD	A,#1 ; Incrementa o contador
		DA	A ; Ajuste do decimal do contador
		DJNZ	R0,SHOW_LOOP ; Decrementa o hexa ate zero
		;CPL	A
		RET
;---------------------------------
; Mostra o valor de A no display
SHOW:		ADD	A,#03
		MOVC	A, @A+PC
		MOV	P1, A
		RET
TAB:		DB 	1h,4Fh,12h,6h,4Ch,24h,20h,0Fh,0h,4h,8h,60h,31h,42h,30h,38h
		END