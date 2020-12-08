		ORG 	0
		SJMP 	PROGRAM
;-------------------------------------------------
PROGRAM:
FLAG_READ	EQU	20h.0; Flag para impedir que leia o mesmo numero varias vezes
			     ;(deve ler antes que nada foi pressionado para aceitar um digito)
LED1		EQU	P3.2
LED2		EQU	P3.4

		SETB	FLAG_READ; Nenhuma tecla apertada
		CLR	LED1; Leds inicialmente apagados
		CLR	LED2; Leds inicialmente apagados

LOOP:		CALL 	READ_KEYBOARD; Retorna o valor da tecla pessionada em R0
		;-------------------------- Confere senha para D1 e D2
		CJNE  	R5,#4,DIGITANDO ; Checa se ja foram digitados 4 digitos
		CJNE  	R1,#03h,TESTE_2
		CJNE  	R2,#0Dh,TESTE_2
		CJNE  	R3,#0Ah,TESTE_2
		CJNE  	R4,#04h,TESTE_2
		CALL 	PERMISSION_1 ; Password certo para combinacao 1
		SJMP 	LOOP
TESTE_2:	CJNE  	R1,#0Eh,WRONG
		CJNE  	R2,#0Bh,WRONG
		CJNE  	R3,#0Ah,WRONG
		CJNE  	R4,#0Ch,WRONG
		CALL 	PERMISSION_2; Password certo para combinacao 2
		SJMP 	LOOP
WRONG:		CALL 	NO_PERMISSION; Password errado
BLOQUEADO:; Estado de bloqueado (loop)
		SETB	LED1
		CLR	LED2
		ACALL 	DELAY_50MS
		CLR	LED1
		SETB	LED2
		ACALL 	DELAY_50MS
		SJMP 	BLOQUEADO
DIGITANDO:	CJNE  	R0, #0FFh, ALGO_DIGITADO
		;-------------------------- Nada digitado (igual a #FFh)
		SETB 	FLAG_READ ; Habilita flag para ler proximo digito
		SJMP 	LOOP

ALGO_DIGITADO:	;-------------------------- Algo digitado (menor que #0Fh)
		JB	FLAG_READ, CONTINUE; Se nao deve ler, volta para o loop
		SJMP 	LOOP
		; Move os registradores para armazenar os ultimos 4 digitados
CONTINUE:	MOV 	A, R3
		MOV 	R4, A; R3->R4
		MOV 	A, R2
		MOV 	R3, A; R2->R3
		MOV 	A, R1
		MOV 	R2, A; R1->R2
		MOV 	A, R0
		MOV 	R1, A; R0->R1
		; Incrementa contador de numeros lidos
		MOV	A, R5
		ADD	A, #1
		MOV	R5, A
		CLR 	FLAG_READ; Espera ate que solte a tecla
		SJMP 	LOOP

DELAY_50MS:
		; START: Wait loop, time: 50 ms
		; Clock: 12000.0 kHz (12 / MC)
		; Used registers: R0, R1, R2
		MOV	R2, #004h
		MOV	R1, #0A0h
		MOV	R0, #025h
		NOP
		DJNZ	R0, $
		DJNZ	R1, $-5
		DJNZ	R2, $-9
		MOV	R0, #021h
		DJNZ	R0, $
		; Rest: 0
		; END: Wait loop

		RET

;-------------------------------------------------
NO_PERMISSION:	; Limpa registradores da senha
		MOV	R0, #0h
		MOV	R1, #0h
		MOV	R2, #0h
		MOV	R3, #0h
		MOV	R4, #0h
		MOV	R5, #0h

		; Preenche memoria externa com FF
		MOV	R0, #0FFh
		MOV	A, #0FFh
PERM_NO_MEM:	MOVX	@R0, A
		DJNZ	R0, PERM_NO_MEM
		MOVX	@R0, A; Endereco zero

		RET
;-------------------------------------------------
PERMISSION_1:	; Limpa registradores da senha
		MOV	R0, #0h
		MOV	R1, #0h
		MOV	R2, #0h
		MOV	R3, #0h
		MOV	R4, #0h
		MOV	R5, #0h
		; Liga led1
		SETB	LED1
		; Preenche memoria externa
		MOV	A, #0FFh
PERM_1_MEM:	MOV	R0, A
		MOVX	@R0, A
		DJNZ	A, PERM_1_MEM
		MOVX	@R0, A; Endereco zero
		
		RET
;-------------------------------------------------
PERMISSION_2:	; Limpa registradores da senha
		MOV	R0, #0h
		MOV	R1, #0h
		MOV	R2, #0h
		MOV	R3, #0h
		MOV	R4, #0h
		MOV	R5, #0h
		; Liga led2
		SETB	LED2
		; Preenche memoria externa com 00
		MOV	R0, #0FFh
		MOV	A, #00h
PERM_2_MEM:	MOVX	@R0, A
		DJNZ	R0, PERM_NO_MEM
		MOVX	@R0, A; Endereco zero

		RET
;-------------------------------------------------
READ_KEYBOARD:	MOV 	P1,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P1.4 ; Zera coluna 0,4,8,C
		JNB	P1.0, ZERO
		JNB	P1.1, QUATRO
		JNB	P1.2, OITO
		JNB	P1.3, CCCC

		MOV 	P1,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P1.5 ; Zera coluna 1,5,9,D
		JNB	P1.0, UM
		JNB	P1.1, CINCO
		JNB	P1.2, NOVE
		JNB	P1.3, DDDD

		MOV 	P1,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P1.6 ; Zera coluna 2,6,A,E
		JNB	P1.0, DOIS
		JNB	P1.1, SEIS
		JNB	P1.2, AAAA
		JNB	P1.3, EEEE

		MOV 	P1,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P1.7 ; Zera coluna 3,7,B,F
		JNB	P1.0, TRES
		JNB	P1.1, SETE
		JNB	P1.2, BBBB
		JNB	P1.3, FFFF

		MOV	R0, #0FFh; Se nao pressionar nada, retorna FF
		RET

ZERO:		MOV R0, #0h
		RET
UM:		MOV R0, #1h
		RET
DOIS:		MOV R0, #2h
		RET
TRES:		MOV R0, #3h
		RET
QUATRO:		MOV R0, #4h
		RET
CINCO:		MOV R0, #5h
		RET
SEIS:		MOV R0, #6h
		RET
SETE:		MOV R0, #7h
		RET
OITO:		MOV R0, #8h
		RET
NOVE:		MOV R0, #9h
		RET
AAAA:		MOV R0, #0Ah
		RET
BBBB:		MOV R0, #0Bh
		RET
CCCC:		MOV R0, #0Ch
		RET
DDDD:		MOV R0, #0Dh
		RET
EEEE:		MOV R0, #0Eh
		RET
FFFF:		MOV R0, #0Fh
		RET

		END
