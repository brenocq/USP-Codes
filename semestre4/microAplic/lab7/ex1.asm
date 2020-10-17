		ORG 	0
		SJMP 	PROGRAM
;--------------------------------------------
		ORG 13h
		SJMP	EXTERN_1
;-------------------------------------------------
PROGRAM:
FLAG_READ	EQU	20h.0; Flag para impedir que leia o mesmo numero varias vezes
			     ;(deve ler antes que nada foi pressionado para aceitar um digito)
FLAG_SECRET	EQU	20h.1; Alterado pela tecla secreta para continuar apos digitar errado
		CLR	FLAG_READ; Nenhuma tecla apertada
		CLR	FLAG_SECRET

		SETB	EA ; Habilita interrupcoes
		SETB	EX1 ; Habilita interrupcao do extern 1
		SETB	IT1 ; Configura interrupcao em borda de descida

LOOP:		CALL 	READ_KEYBOARD; Retorna o valor da tecla pessionada em R0
		CJNE  R0,#0Fh,NOTEQUAL ; Checa qual tecla foi apertada
		;-------------------------- Apertou hashtag
		CJNE  R1,#03h,WRONG
		CJNE  R2,#0Bh,WRONG
		CJNE  R3,#0Ah,WRONG
		CJNE  R4,#07h,WRONG
		CALL PERMISSION ; Password certo
		SJMP 	LOOP
WRONG:		CALL NO_PERMISSION; Password errado
		SJMP 	LOOP
NOTEQUAL:	JC LESS
		;-------------------------- Nada digitado (maior que #0Fh)
		SETB FLAG_READ ; Habilita flag para ler proximo digito
		SJMP 	LOOP
LESS:		;-------------------------- Algo digitado (menor que #0Fh)
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
		CLR 	FLAG_READ; Espera ate que solte a tecla
		SJMP 	LOOP

;-------------------------------------------------
EXTERN_1:	SETB FLAG_SECRET
		RETI

;-------------------------------------------------
NO_PERMISSION:	MOV	P2, #01010101b; Coloca leds para alternar
		CLR	FLAG_SECRET ; Somente se apertar o botao secreto a partir de agora
		; Limpa registradores da senha
		MOV	R0, #0h
		MOV	R1, #0h
		MOV	R2, #0h
		MOV	R3, #0h
		MOV	R4, #0h
		CALL DELAY
NO_PERM_LOOP:	MOV	A, P2
		RL 	A
		MOV	P2, A
		CALL DELAY
		JB	FLAG_SECRET, NO_PERM_END ; Checa se a tecla secreta foi pressionada
		SJMP 	NO_PERM_LOOP
NO_PERM_END:	MOV	P2, #0FFh
		CLR	FLAG_SECRET
		RET
;-------------------------------------------------
PERMISSION:	; Limpa registradores da senha
		MOV	R0, #0h
		MOV	R1, #0h
		MOV	R2, #0h
		MOV	R3, #0h
		MOV	R4, #0h
		; Acende os LEDS do LSB para o MSB
		MOV	P2, #0FFh
		CLR	P2.0
		CALL DELAY
		CLR	P2.1
		CALL DELAY
		CLR	P2.2
		CALL DELAY
		CLR	P2.3
		CALL DELAY
		CLR	P2.4
		CALL DELAY
		CLR	P2.5
		CALL DELAY
		CLR	P2.6
		CALL DELAY
		CLR	P2.7
		CALL DELAY
		RET
;-------------------------------------------------
DELAY:		; Delay 25us
		MOV	R5, #0Bh
		NOP
		DJNZ	R5, $
		RET
;-------------------------------------------------
READ_KEYBOARD:	MOV 	P1,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P1.4 ; Zera coluna 1,4,7,*
		JNB	P1.0, UM
		JNB	P1.1, QUATRO
		JNB	P1.2, SETE
		JNB	P1.3, ASTE

		MOV 	P1,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P1.5 ; Zera coluna 2,5,8,0
		JNB	P1.0, DOIS
		JNB	P1.1, CINCO
		JNB	P1.2, OITO
		JNB	P1.3, ZERO

		MOV 	P1,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P1.6 ; Zera coluna 3,6,9,#
		JNB	P1.0, TRES
		JNB	P1.1, SEIS
		JNB	P1.2, NOVE
		JNB	P1.3, HASH

		MOV 	P1,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P1.7 ; Zera coluna A,B,C,D
		JNB	P1.0, AAAA
		JNB	P1.1, BBBB
		JNB	P1.2, CCCC
		JNB	P1.3, DDDD

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
ASTE:		MOV R0, #0Eh
		RET
HASH:		MOV R0, #0Fh
		RET

		END