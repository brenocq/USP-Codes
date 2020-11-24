		ORG 	0
		SJMP 	PROGRAM
;--------------------------------------------
		ORG 13h
		SJMP	EXTERN_1
;--------------------------------------------
PROGRAM:
FLAG_COUNT	EQU	20h.0; Flag para contador (1: pausado, 0: contando)
		SETB 	EA ; Habilita interrupções
		SETB 	EX1 ; Habilita a interrupção zero
		SETB 	IT1 ; Interrupção em borda de descida

		; Limpa displays
		MOV	P0,#0
		MOV	P1,#0
		MOV	P2,#0
		; Inicializa contador
		MOV	R0,#0
		CLR	FLAG_COUNT
LOOP:
		JB	FLAG_COUNT, LOOP
		CALL	DISPLAY; Impreme numero de 3 digitos
		; Incrementa contador
		MOV	A,R0
		ADD	A,#1
		MOV	R0,A
		CJNE  	R0,#200,NOTEQUAL
		MOV	R0,#0
NOTEQUAL:	SJMP LOOP

;---------------------------------
; Converte o valor de R0 para BCD
R0_TO_BCD:	; LSB -> R1
		; ISB -> R2
		; MSB -> R3
		MOV	A,R0

		; Processa R3
		CJNE  	A,#100,NOTEQUAL_100
NOTEQUAL_100:	JC 	GREATER_100
		MOV 	R3,#1
		SUBB 	A,#100
		SJMP	R3_CALCULATED
GREATER_100:	MOV 	R3,#0

R3_CALCULATED:	MOV	R1,A
; greater code goes here
		; Converte para BCD
		CJNE	A,#00,TESTE
ZERO:		;CPL	A
		; Se for zero, retorna zero
		MOV 	R1,#0
		MOV 	R2,#0
		MOV 	R3,#0
		RET

TESTE:		CLR	A ; Inicializa o contador BCD em zero
SHOW_LOOP:	ADD	A,#1 ; Incrementa o contador
		DA	A ; Ajuste do decimal do contador
		DJNZ	R1,SHOW_LOOP ; Decrementa o hexa ate zero
		; Processa R1
		MOV	R2,A
		ANL	A,#00001111b
		MOV	R1,A

		; Processa R2
		MOV	A,R2
		ANL	A,#11110000b
		SWAP	A
		MOV	R2,A
		
		RET
;---------------------------------
; Mostra o valor de R0 no display
DISPLAY:	; Converte contador para BCD (retorno em R3, R2, R1)
		CALL	R0_TO_BCD
		; Mostra display menos significativo
		MOV	A,R1
		ADD	A,#15
		MOVC	A,@A+PC
		MOV	P0,A
		; Mostra display do meio
		MOV	A,R2
		ADD	A,#09
		MOVC	A,@A+PC
		MOV	P2,A
		; Mostrar display mais significativo
		MOV	A,R3
		ADD	A,#03
		MOVC	A,@A+PC
		MOV	P1,A
		RET
TAB:		DB 	3Fh,06h,5Bh,4Fh,66h,6Dh,7Dh,07h,7Fh,6Fh

EXTERN_1:	CLR	EA
		JB	FLAG_COUNT, CONTINUE
		SETB	FLAG_COUNT
		SETB	EA
		RETI
CONTINUE:	CLR	FLAG_COUNT
		SETB	EA
		RETI
		END