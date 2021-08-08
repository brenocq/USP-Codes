		ORG 	0
		SJMP 	PROGRAM
;--------------------------------------------
		ORG 	3h
		SJMP	EXTERN_0
;--------------------------------------------
		ORG 	0Bh
		CPL	P3.6
		RETI
;--------------------------------------------
PROGRAM:
		SETB 	EA ; Habilita interrupções
		SETB 	EX0 ; Habilita a interrupção zero
		SETB 	IT0 ; Interrupção em borda de descida

		SETB	ET0; Habilita timer 0
		MOV	TH0, #0B9h; Timer para 70us (70us nivel alto, 70us nivel baixo -> 140us de periodo)
		MOV	TL0, #0B9h
		MOV	TMOD, #2; Timer no modo 2
		SETB	TR0; Inicializa timer 0

		; Limpa display
		MOV	P2,#0
LOOP:		ACALL 	DISPLAY
		SJMP 	LOOP

;---------------------------------
; Mostra o valor de R0 no display
DISPLAY:	;CALL	R0_TO_BCD
		; Seleciona display mais significativo
		MOV	P2,#0
		SETB	P3.7
		; Mostra display mais significativo
		MOV	A,31h
		ADD	A,#15
		MOVC	A,@A+PC
		MOV	P2,A
		; Seleciona display menos significativo
		MOV	P2,#0
		CLR	P3.7
		; Mostra display menos significativo
		MOV	A,30h
		ADD	A,#03
		MOVC	A,@A+PC
		MOV	P2,A
		RET
TAB:		DB 	7Eh,30h,6Dh,79h,33h,5Bh,5Fh,70h,7Fh,7Bh
;--------------------------------
EXTERN_0:	CLR	EA
		MOV	R0, A; Salva valor de A
		MOV	A, P1
		CJNE  	A,#0A0h, NOTEQUAL_P1
NOTEQUAL_P1:	JC 	LESS_P1
		; Igual ou maior que A0
		MOV	31h, #1; Salva 31h
		SWAP	A
		ANL	A, #00001111b
		CLR 	C
		SUBB	A, #0Ah
		MOV	30h, A; Salva 30h
		SETB	EA
		MOV	A, R0
		RETI
LESS_P1:	; Menor que A0
		MOV	31h, #0; Salva 31h
		SWAP	A
		ANL	A, #00001111b
		MOV	30h, A; Salva 30h
		SETB	EA
		MOV	A, R0
		RETI
		END
