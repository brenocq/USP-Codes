		ORG 	0
		SJMP 	PROGRAM
;--------------------------------------------
		ORG 	3h
		SJMP	EXTERN_0
;--------------------------------------------
		ORG 	13h
		SJMP	EXTERN_1
;--------------------------------------------
PROGRAM:
MP_C		EQU	P1.2
MP_D		EQU	P1.3
MP_P		EQU	P1.4
SEL_LSB		EQU	P3.6
SEL_MSB		EQU	P3.7
RAM_LSB		EQU	30h
RAM_MSB		EQU	31h
CONTAR_TAM	EQU	20h.1
PECA_LIDA	EQU	20h.2

		; Interrupcoes
		SETB 	EA ; Habilita interrupções
		SETB 	EX0 ; Habilita a interrupção zero
		SETB 	IT0 ; Interrupção em borda de descida
		SETB 	EX1 ; Habilita a interrupção um
		SETB 	IT1 ; Interrupção em borda de descida

		; Flags
		CLR 	CONTAR_TAM; Inicialmente nao ira contar o tamanho da peca
		CLR	PECA_LIDA; Inicialmente ainda nao leu nenhuma peca

		; Limpa buffer
		MOV	RAM_LSB, #0
		MOV	RAM_MSB, #0

		; Limpa display
		MOV	P2,#0
		SETB 	SEL_LSB
		SETB 	SEL_MSB

		; Inicializa motor (objeto antes do primeiro sensor)
		SETB	MP_P
		SETB	MP_D; Move da esquerda para a direita
		; Loop
LOOP:		ACALL 	DISPLAY
		ACALL	MOVE_MOTOR
		SJMP 	LOOP

;---------------------------------
; Mostra o valor de R0 no display
DISPLAY:	;CALL	R0_TO_BCD
		
		; Seleciona display mais significativo
		SETB 	SEL_MSB
		CLR 	SEL_LSB
		MOV	P2,#0
		; Mostra display mais significativo
		MOV	A,RAM_MSB
		ADD	A,#17
		MOVC	A,@A+PC
		MOV	P2,A
		; Seleciona display menos significativo
		CLR 	SEL_MSB
		SETB 	SEL_LSB
		MOV	P2,#0
		; Mostra display menos significativo
		MOV	A,RAM_LSB
		ADD	A,#03
		MOVC	A,@A+PC
		MOV	P2,A
		RET
TAB:		DB 	7Eh,30h,6Dh,79h,33h,5Bh,5Fh,70h,7Fh,7Bh
;--------------------------------
MOVE_MOTOR:	CPL	MP_C
		;ACALL	DELAY_MOTOR
		CPL	MP_C
		;ACALL	DELAY_MOTOR
		JB	CONTAR_TAM, MOVE_CONTA
		SJMP	MOVE_FIM
	
MOVE_CONTA:	MOV	A, R7
		ADD	A, #1
		MOV	R7, A
MOVE_FIM:	RET
DELAY_MOTOR:
		; START: Wait loop, time: 2.5 ms
		; Clock: 12000.0 kHz (12 / MC)
		; Used registers: R0, R1
		MOV	R1, #006h; <-- Parametros de tempo utilizado para simular clock para passo do motor
		MOV	R0, #0CEh; <--
		NOP
		DJNZ	R0, $
		DJNZ	R1, $-5
		NOP
		NOP
		NOP
		; Rest: 0
		; END: Wait loop
		RET
;--------------------------------
EXTERN_0:	CLR	EA; Desabilita interrupcoes

		CLR	PECA_LIDA; Se chegar outra peca ela sera lida

		MOV	A, RAM_MSB
		ADD	A, #1; Incrementa quantidade de pecas
		MOV	RAM_MSB, A; Quantidade de pecas
		MOV	RAM_LSB, R7; Tamanho da peca
		MOV	R7, #0; Limpa contador de tamanho

		SETB	EA; Habilita interrupcoes
		RETI
;--------------------------------
EXTERN_1:	CLR	EA; Desabilita interrupcoes

		; Se esta movendo para a direita e ainda nao leu a peca, comeca a ler
		JB	MP_D, MOVENDO_DIR
		SJMP	MOVENDO_ESQ
MOVENDO_DIR:	JB	PECA_LIDA, EXTERN_FIM; Se ja leu, continua para passar pelo sensor 0
		SETB	CONTAR_TAM
		CLR	MP_D; Inverte direcao -> ira comecar a ler, move para esquerda
		SJMP	EXTERN_FIM
MOVENDO_ESQ:	; Se esta movendo para a esquerda, terminou a leitura do tamanho
		CLR	CONTAR_TAM
		SETB	PECA_LIDA
		SETB	MP_D; Inverte direcao -> terminou de ler, move para direita

EXTERN_FIM:	SETB	EA; Habilita interrupcoes
		RETI
		END

