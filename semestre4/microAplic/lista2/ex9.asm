		ORG 	0
		SJMP 	PROGRAM
;--------------------------------------------
PROGRAM:
MOTOR		EQU	P3.5
DIGIT		EQU	20h.0
FLAG_READ	EQU	20h.1
ENAB 		EQU	P3.0
RS 		EQU	P3.2
RW 		EQU	P3.1
D 		EQU	P2

		; Contador e timer
		; O timer esta sendo utilizado para detectar quando o INT1=1 (muito tempo sem INT1=0)
		MOV	TMOD, #00000101b; Contador por hardware T0 + contador 16 bits
		SETB 	TR0; Inicia contador

		; Inicializacoes
		CLR 	MOTOR; Motor comeca desligado
		CLR	DIGIT; Primeiro digito
		CLR	FLAG_READ; Nenhuma tecla apertada

		;---- Inicializa o display
		LCALL INIT_LCD
		LCALL CLEAR_LCD
		MOV	A, #00h; Posicao do cursor no inicio
		LCALL 	POS_LCD

		; Loop
LOOP:
		; Entrada no teclado de ate dois digitos
		ACALL	READ_KEYBOARD
		CJNE  	R1,#0FFh,ALGO_DIGITADO
		CLR	FLAG_READ; Pode ler proximo numero
		SJMP	LOOP
ALGO_DIGITADO:	JB	FLAG_READ, LOOP; Espera ler FF para ler proximo numero (soltar a tecla)
		JB	DIGIT, SEGUNDO_DIGITO
		; Ler primeiro digito
		MOV	A, R1
		MOV	B, #0Ah
		MUL	AB; Multiplica por 10
		MOV	R0, A
		SETB	FLAG_READ; Algo digitado
		SETB	DIGIT; Proxima leitura segundo digito
		SJMP	LOOP
SEGUNDO_DIGITO:	; Ler segundo digito
		MOV	A, R1
		ADD	A, R0; Adiciona unidades
		MOV	R0, A
		SETB	FLAG_READ; Algo digitado
		CLR	DIGIT; Proxima leitura primeiro digito

		; Entrada recebida de dois digitos (R0), esperar contador
		MOV	TH0, #0
		MOV	TL0, #0

		SETB	MOTOR; Liga o motor
WAIT:		MOV	A, R0
		CLR	C
		SUBB	A, TL0
		; Se A == 0, valores iguais
		CJNE	A,#0, COMP_OF
		SJMP	POSICIONADO
COMP_OF:	; Se A >=100, overflow (TL0>A)
		CJNE	A,#100, COMP_DIFF
COMP_DIFF:	JNC POSICIONADO
		SJMP	WAIT; A<100, ainda nao posicionado
POSICIONADO:
		CLR	MOTOR; Para o motor
		; Impreme mensagem no LCD e continua esperando proxima entrada
		LCALL	PRINT_MESSAGE
		MOV	R0, #0
		SJMP 	LOOP
;-------------------------------------------------
; Retorna valor digitado em R1
READ_KEYBOARD:	MOV 	P1,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P1.0
		JNB	P1.4, ZERO
		JNB	P1.5, UM
		JNB	P1.6, DOIS

		MOV 	P1,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P1.1
		JNB	P1.4, TRES
		JNB	P1.5, QUATRO
		JNB	P1.6, CINCO

		MOV 	P1,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P1.2
		JNB	P1.4, SEIS
		JNB	P1.5, SETE
		JNB	P1.6, OITO

		MOV 	P1,#0FFh ; Garante nivel logico 1 em todos os bits de P1
		CLR 	P1.3
		JNB	P1.5, NOVE

		MOV	R1, #0FFh; Se nao pressionar nada, retorna FF
		RET

ZERO:		MOV R1, #0h
		RET
UM:		MOV R1, #1h
		RET
DOIS:		MOV R1, #2h
		RET
TRES:		MOV R1, #3h
		RET
QUATRO:		MOV R1, #4h
		RET
CINCO:		MOV R1, #5h
		RET
SEIS:		MOV R1, #6h
		RET
SETE:		MOV R1, #7h
		RET
OITO:		MOV R1, #8h
		RET
NOVE:		MOV R1, #9h
		RET

;------------------------------------------------- Funções do LCD
PRINT_MESSAGE:
		MOV	A, #'F'
		
		MOV	R0, #22; Numero de caracteres na string
SEND_S_PRINT:	CJNE	A, #' ', CONTINUE_PRINT
		MOV	A, #40h; Move cursor para segunda linha se espaco
		LCALL 	POS_LCD
CONTINUE_PRINT:	MOV	A, #22
		CLR 	C
		SUBB	A,R0
		ADD	A,#6
		MOVC	A,@A+PC
		LCALL	WRITE_TEXT; Escreve no LCD
		DJNZ	R0, SEND_S_PRINT
		RET
TAB:		DB 	'FERRAMENTA POSICIONADA'

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



