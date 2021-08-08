		ORG 	0
		SJMP 	PROGRAM
;-------------------------------------------------
PROGRAM:
FLAG_READ	EQU	20h.0; Flag para impedir que leia o mesmo numero varias vezes
			     ;(deve ler antes que nada foi pressionado para aceitar um digito)
FLAG_WRONG	EQU	20h.1; Habilitada qundo uma senha errada for digitada e precisar desbloquear
ENAB 		EQU	P3.0
RS 		EQU	P3.2
RW 		EQU	P3.1
D 		EQU	P2

		CLR	FLAG_READ; Nenhuma tecla apertada
		CLR	FLAG_WRONG; Nenhuma senha errada
		CLR	D1; Desabilita dispositivo D1
		CLR	D2; Desabilita dispositivo D2
		CLR	ALARME; Desliga o alarme

		;---- Inicializa o display
		LCALL INIT_LCD
		LCALL CLEAR_LCD
		MOV	A, #00h; Posicao do cursor no inicio
		LCALL 	POS_LCD

		MOV	A, #'F'
		LCALL	WRITE_TEXT; Escreve no LCD

LOOP:		CALL 	READ_KEYBOARD; Retorna o valor da tecla pessionada em R0
		;-------------------------- Confere senha para D1 e D2
		CJNE  	R5,#4,DIGITANDO ; Checa se ja foram digitados 4 digitos
		JB	FLAG_WRONG, DESBLOQUEIO; Se estiver aguardando senha para parar alarme...
		CJNE  	R1,#0Fh,TESTE_D2
		CJNE  	R2,#02h,TESTE_D2
		CJNE  	R3,#04h,TESTE_D2
		CJNE  	R4,#0Ch,TESTE_D2
		CALL 	PERMISSION_D1 ; Password certo para D1
		SJMP 	LOOP
TESTE_D2:	CJNE  	R1,#0Ch,WRONG
		CJNE  	R2,#04h,WRONG
		CJNE  	R3,#02h,WRONG
		CJNE  	R4,#0Fh,WRONG
		CALL 	PERMISSION_D2; Password certo para D2
		SJMP 	LOOP
DESBLOQUEIO:	CJNE  	R1,#0Fh,WRONG
		CJNE  	R2,#02h,WRONG
		CJNE  	R3,#04h,WRONG
		CJNE  	R4,#0Ch,WRONG
		CALL 	PERMISSION_ALARME ; Password certo para desligar alarme
WRONG:		CALL 	NO_PERMISSION; Password errado
		SJMP 	LOOP
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

;-------------------------------------------------
NO_PERMISSION:	SETB	ALARME; Aciona o alarme
		CLR	D1; Zera D1
		CLR	D2; Zera D2
		SETB	FLAG_WRONG ; Somente se apertar o botao secreto a partir de agora
		; Limpa registradores da senha
		MOV	R0, #0h
		MOV	R1, #0h
		MOV	R2, #0h
		MOV	R3, #0h
		MOV	R4, #0h
		MOV	R5, #0h
		RET
PERMISSION_ALARME:
		CLR	ALARME; Desliga o alarme
		CLR	FLAG_WRONG ; Espera senhas para D1 e D2
		; Limpa registradores da senha
		MOV	R0, #0h
		MOV	R1, #0h
		MOV	R2, #0h
		MOV	R3, #0h
		MOV	R4, #0h
		MOV	R5, #0h
		RET
;-------------------------------------------------
PERMISSION_D1:	; Limpa registradores da senha
		MOV	R0, #0h
		MOV	R1, #0h
		MOV	R2, #0h
		MOV	R3, #0h
		MOV	R4, #0h
		MOV	R5, #0h
		; Fecha/abre a fechadura atraves do dispositivo D1
		JB	D1, DESLIGA_D1
		SETB	D1
		RET
DESLIGA_D1:	CLR	D1
		RET
;-------------------------------------------------
PERMISSION_D2:	; Limpa registradores da senha
		MOV	R0, #0h
		MOV	R1, #0h
		MOV	R2, #0h
		MOV	R3, #0h
		MOV	R4, #0h
		MOV	R5, #0h
		; Fecha/abre a fechadura atraves do dispositivo D2
		JB	D2, DESLIGA_D2
		SETB	D2
		RET
DESLIGA_D2:	CLR	D2
		RET
;-------------------------------------------------
READ_KEYBOARD:	MOV 	P2,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P2.4 ; Zera coluna 0,4,8,C
		JNB	P2.0, ZERO
		JNB	P2.1, QUATRO
		JNB	P2.2, OITO
		JNB	P2.3, CCCC

		MOV 	P2,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P2.5 ; Zera coluna 1,5,9,D
		JNB	P2.0, UM
		JNB	P2.1, CINCO
		JNB	P2.2, NOVE
		JNB	P2.3, DDDD

		MOV 	P2,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P2.6 ; Zera coluna 2,6,A,E
		JNB	P2.0, DOIS
		JNB	P2.1, SEIS
		JNB	P2.2, AAAA
		JNB	P2.3, EEEE

		MOV 	P2,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P2.7 ; Zera coluna 3,7,B,F
		JNB	P2.0, TRES
		JNB	P2.1, SETE
		JNB	P2.2, BBBB
		JNB	P2.3, FFFF

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

;------------------------------------------------- Funções do LCD
INIT_LCD:	CLR	RW
		SETB	ENAB
		CLR	RS
		MOV	D, #38h
		CLR	ENAB
		LCALL	WAIT_LCD
		;------
		SETB	ENAB
		CLR	RS
		MOV	D, #0Eh
		CLR	ENAB
		CALL	WAIT_LCD
		;------
		SETB	ENAB
		CLR	RS
		MOV	D, #06h
		CLR	ENAB
		LCALL	WAIT_LCD	
		RET
;-----------------
CLEAR_LCD:	CLR	RW
		SETB	ENAB
		CLR	RS
		MOV	D, #01h
		CLR	ENAB
		LCALL	WAIT_LCD
		RET
;-----------------
POS_LCD:	CLR	RW
		SETB	ENAB
		CLR	RS
		ADD	A, #80h
		MOV	D, A
		CLR	ENAB
		LCALL	WAIT_LCD
		RET
;-----------------
WRITE_TEXT:	CLR	RW
		SETB	ENAB
		SETB	RS
		MOV	D, A
		CLR	ENAB
		LCALL	WAIT_LCD
		RET
;-----------------
WAIT_LCD:	SETB	RW
		SETB	ENAB
		CLR	RS
		MOV	D, #0FFh
		;JB	D.7, $

		CLR	ENAB
		CLR	RW
		RET
		
		END