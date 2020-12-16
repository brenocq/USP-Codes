		ORG 	0
		LJMP	PROGRAM
;--------------------------------------------
		ORG 	3h
		LJMP	EXTERN_0
;--------------------------------------------
		ORG 	13h
		LJMP	EXTERN_1
		RETI
;--------------------------------------------
		ORG 	23h
		LJMP	SERIAL
;--------------------------------------------
		ORG 	2001h; Rodar programa na memoria externa
PROGRAM:
LIDO_ADC	EQU	R0
COUNT_50MS	EQU	R1
RAM_LSB		EQU	30h
RAM_MSB		EQU	31h
; LCD info
ENAB 		EQU	P1.2
RS 		EQU	P1.0
RW 		EQU	P1.1
; Flags
FLAG_S		EQU	20h.0; Flag de atendimento a serial
OPT_LIDO	EQU	20h.1; Flag de sensor optico leu alguma coisa
; Time control
MS_TICK		EQU	33h; Aumenta a cada 10ms (ate 100)
S_TICK		EQU	34h; Aumenta a cada segundo (ate 10)
; Controle motores
MOTOR_BOB	EQU	35h; Index da bobina ativa nos motores de passo
; Controle teclado
QTD_DIG		EQU	36h; Quantos caracteres foram digitados
DIG_0		EQU	37h
DIG_1		EQU	38h
DIG_2		EQU	39h
DIG_3		EQU	40h

COMECA_PROG	EQU	20h.2
PARA_PROG	EQU	20h.3

		;------------------ Inicializacoes ------------------
		; Comeca a escrever na 800Fh da RAM externa (8000-800D sao perifericos)
		MOV	RAM_MSB, #80h
		MOV	RAM_LSB, #0Fh
		MOV	MS_TICK, #0h
		MOV	S_TICK, #0h
		CLR	OPT_LIDO; Sensor optico nao leu nada
		MOV	MOTOR_BOB, #0h; Bobina zera sera a primeira ativa ao ligar motores
		MOV	QTD_DIG, #0; Inicialmente nada digitado
		CLR	COMECA_PROG
		CLR	PARA_PROG

		;--------------------- Interrupcoes ------------------
		SETB 	EA ; Habilita interrupções
		SETB 	EX0 ; Habilita a interrupção 0
		SETB 	IT0 ; Interrupção 0 em borda de descida
		SETB 	EX1 ; Habilita a interrupção 1
		SETB 	IT1 ; Interrupção 1 em borda de descida

		;----------------- Contador encoder -----------------
		MOV	TMOD, #00000101b; Contador por hardware T0 + contador 16 bits
		SETB 	TR0; Inicia contador

		;------------------------ Serial --------------------
		SETB	IE.4; Habilita interrupcao serial
		; Configurando Comunicacao com 9600
		MOV 	PCON, #10000000b
		MOV 	TH1,#250
		MOV 	TL1,#250
		; Modo 2 de comunicacao
		SETB 	TR1
		MOV 	SCON,#1000000b
		SETB 	REN ; Habilita a Recepção

		;------------------------ Display -------------------
		LCALL 	INIT_LCD
		LCALL 	CLEAR_LCD
		MOV	A, #00h; Posicao do cursor no inicio
		LCALL 	POS_LCD


		MOV	DPTR, #8000h
		MOVX	@DPTR, A; Chama ADC para ler o primeiro numero (ja estara pronto pelo tempo de espera)
		CALL	DELAY_10MS

		; Inicializa os motores 1 e 2 (desligado)
		MOV	A, #0
		MOV	DPTR, #800Bh
		MOVX	@DPTR, A
		; Inicializa os motores 3 e 4 (desligado)
		MOV	DPTR, #800Ch
		MOVX	@DPTR, A

		; Inicializa teclado totalmente ligado para receber interrupcao
		MOV	DPTR, #800Ah
		MOV	A, #0
		MOVX	@DPTR, A

		JNB	COMECA_PROG, $
LOOP:		JNB	PARA_PROG, $
		ACALL 	PROG_PAROU
CONTINUA_LOOP:
		;----------------- Executa a cada 10 ms ----------------;
		CALL 	LER_CONVERSOR; Le ADC, manda para DAC
		CALL	ENVIA_LCD_SERIAL; Escreve LCD, envia serial
		CALL	ACENDE_LEDS
		CALL	DELAY_10MS

		; Move motores se necessario (100Hz - a cada 10ms)
		JNB	OPT_LIDO, MOTOR_DESLIGADO
		ACALL	MOVE_MOTORES
MOTOR_DESLIGADO:

		; Incrementa tick de 10ms
		MOV	A, MS_TICK
		ADD	A, #1
		MOV	MS_TICK, A

		; Se chegou em 100 ticks (1 segundo)
		CJNE	A, #100, LOOP
		;----------------- Executa a cada 1 segundo ----------------;
		ACALL	EACH_SECOND

		MOV	MS_TICK, #0
		; Incrementa tick de 1s
		MOV	A, S_TICK
		ADD	A, #1
		MOV	S_TICK, A

		CJNE	A, #10, LOOP
		;----------------- Executa a cada 10 segundos ----------------;
		MOV	S_TICK, #0

		; Imprime pulsos no encoder se necessario
		JNB	OPT_LIDO, NAO_CONTA_ENC
		ACALL	CONTA_ENCODER
NAO_CONTA_ENC:
		SJMP 	LOOP
;-----------------------------
LER_CONVERSOR:
		; Desabilitar interrupcoes para impedir que o DPTR seja alterado
		CLR 	EA ; Desabilita interrupções
		; Le valor do primeiro ADC
		MOV	DPTR, #8000h
		MOVX	A, @DPTR
		MOVX	@DPTR, A; Chama ADC para ler proximo (ja estara pronto pelo tempo de espera)

		; Escreve valor no DAC
		MOV	DPTR, #8008h
		MOVX	@DPTR, A
		SETB 	EA ; Habilita interrupções

		MOV	LIDO_ADC, A

		RET
;-----------------
ENVIA_LCD_SERIAL:
		;------------ Escreve valor LCD ---------------
		; Move cursor para inicio
		MOV	A, #00h; Posicao do cursor no inicio
		LCALL 	POS_LCD
		; Manda valor lido para LCD
		MOV	A, LIDO_ADC
		MOV	R2, A
		ACALL 	R2_TO_LCD
		;---------------- Envia serial -----------------
		; Manda valor lido para Serial
		MOV	A, LIDO_ADC
		MOV 	SBUF, A
		CLR	FLAG_S
		JNB	FLAG_S, $
		RET
;-----------------
ACENDE_LEDS:
		MOV	A, LIDO_ADC
		MOV	B, #32
		DIV	AB
		; Apos a divisao o A armazena o indice do led para acender
		MOV	R2,A
		MOV	A, #10000000b
LED_ROTATE_LEFT:RL	A
		DJNZ	R2, LED_ROTATE_LEFT

		MOV	DPTR, #800Dh
		MOVX	@DPTR, A

		RET
;------------------
MOVE_MOTORES:	
		; Calcula bobina ativa
		; 0-> 0001
		; 1-> 0010
		; 2-> 0100
		; 3-> 1000
		
		MOV	A, #10000000b
		MOV	R2, MOTOR_BOB
MOTOR_ROTATE_LEFT:
		RL	A
		DJNZ	R2, MOTOR_ROTATE_LEFT

		; Transforma A
		; ex: 0000 0010 -> 0010 0010
		MOV	B, A
		RL	A
		RL	A
		RL	A
		RL	A
		ADD	A, B

		; Rotaciona os motores 1 e 2
		MOV	DPTR, #800Bh
		MOVX	@DPTR, A
		; Inicializa os motores 3 e 4
		MOV	DPTR, #800Ch
		MOVX	@DPTR, A

		; Move index da bobina ativa para o proximo
		MOV	A, MOTOR_BOB
		ADD	A, #1
		MOV	MOTOR_BOB, A
		
		CJNE	A, #4, MOVER_MOTOR_FIM
		MOV	MOTOR_BOB, #0
MOVER_MOTOR_FIM:
		RET
;-----------------------------
CONTA_ENCODER:
		;------------ Escreve valor do encoder no LCD (0000 ate FFFF)---------------
		; Move cursor para inicio
		MOV	A, #40h; Posicao do cursor no inicio da segunda linha
		LCALL 	POS_LCD

		;------- Manda valor lido para LCD (Th0)-------
		; Escreve MSB
		MOV	A, TH0
		SWAP	A
		ORL	A, #00001111b
		
		MOV	R2, A
		ACALL 	R2_TO_LCD

		; Escreve LSB
		MOV	A, TH0
		ORL	A, #00001111b
		
		MOV	R2, A
		ACALL 	R2_TO_LCD
		
		;------- Manda valor lido para LCD (TL0)-------
		; Escreve MSB
		MOV	A, TL0
		SWAP	A
		ORL	A, #00001111b
		
		MOV	R2, A
		ACALL 	R2_TO_LCD

		; Escreve LSB
		MOV	A, TL0
		ORL	A, #00001111b
		
		MOV	R2, A
		ACALL 	R2_TO_LCD

		CLR	OPT_LIDO; Para de mover motores e "ler encoder"
		RET
;-----------------------------
DELAY_10MS:
		; START: Wait loop, time: 10 ms
		; Clock: 12000.0 kHz (12 / MC)
		; Used registers: R7, R6
		MOV	R6, #015h
		MOV	R7, #0ECh
		NOP
		DJNZ	R7, $
		DJNZ	R6, $-5
		NOP
		RET
;-----------------------------
EACH_SECOND:; Executa a cada 1 segundo
		; Seta endereco DPTR
		MOV	DPH, RAM_MSB
		MOV	DPL, RAM_LSB

		; Salva valor do ADC lido no endereco
		MOV	A, LIDO_ADC
		MOVX	@DPTR, A

		;  Checa posicao DPTR
		MOV	A, DPH
		CJNE	A, #0FFh, NOT_FIM_RAM
		MOV	A, DPL
		CJNE	A, #0FFh, NOT_FIM_RAM
		; Se fim da RAM...
		MOV	DPH, #80h
		MOV	DPL, #0Dh

NOT_FIM_RAM:	; Proximo endereco DPTR
		INC 	DPTR
		MOV	RAM_MSB, DPH
		MOV	RAM_LSB, DPL
		
		RET
;-----------------------------
PROG_PAROU:
		ACALL	PRINT_PAROU; Imprime no LCD e envia na serial ao mesmo tempo
		SJMP	$
		RET
		
PRINT_PAROU:	
		MOV	A, #'P'
		
		MOV	R0, #17; Numero de caracteres na string
PRINT_PAROU_NE:	CJNE	A, #' ', PRINT_PAROU_CO; Continua print
		MOV	A, #40h; Move cursor para segunda linha se espaco
		LCALL 	POS_LCD
PRINT_PAROU_CO:	MOV	A, #17
		CLR 	C
		SUBB	A,R0
		ADD	A,#12
		MOVC	A,@A+PC
		LCALL	WRITE_TEXT; Escreve no LCD
		MOV 	SBUF, A
		CLR	FLAG_S
		JNB	FLAG_S, $; Manda na serial
		DJNZ	R0, PRINT_PAROU_NE
		RET
TAB2:		DB 	'Programa suspenso'

;-----------------------------
LE_TECLADO:
		MOV	DPTR, #800Ah

		MOV 	A,#01111111b ; Somente columa 1 zerada
		MOVX	@DPTR, A
		MOVX	A, @DPTR; Le valor da coluna 1

		CLR 	A.4 ; Zera coluna 1,4,7,*
		JNB	A.4, UM
		JNB	A.5, QUATRO
		JNB	A.6, SETE
		JNB	A.7, EEEE

		MOV 	A,#10111111b ; Somente columa 2 zerada
		MOVX	@DPTR, A
		MOVX	A, @DPTR; Le valor da coluna 2

		JNB	A.4, DOIS
		JNB	A.5, CINCO
		JNB	A.6, OITO
		JNB	A.7, ZERO

		MOV 	A,#11011111b ; Somente columa 3 zerada
		MOVX	@DPTR, A
		MOVX	A, @DPTR; Le valor da coluna 3

		JNB	A.4, TRES
		JNB	A.5, SEIS
		JNB	A.6, NOVE
		JNB	A.7, FFFF

		MOV 	A,#11101111b ; Somente columa 4 zerada
		MOVX	@DPTR, A
		MOVX	A, @DPTR; Le valor da coluna 4

		JNB	A.4, AAAA
		JNB	A.5, BBBB
		JNB	A.6, CCCC
		JNB	A.7, DDDD

		SJMP	NADA_LIDO

ZERO:		MOV R0, #0h
		SJMP	LE_TECLADO_OK
UM:		MOV R0, #1h
		SJMP	LE_TECLADO_OK
DOIS:		MOV R0, #2h
		SJMP	LE_TECLADO_OK
TRES:		MOV R0, #3h
		SJMP	LE_TECLADO_OK
QUATRO:		MOV R0, #4h
		SJMP	LE_TECLADO_OK
CINCO:		MOV R0, #5h
		SJMP	LE_TECLADO_OK
SEIS:		MOV R0, #6h
		SJMP	LE_TECLADO_OK
SETE:		MOV R0, #7h
		SJMP	LE_TECLADO_OK
OITO:		MOV R0, #8h
		SJMP	LE_TECLADO_OK
NOVE:		MOV R0, #9h
		SJMP	LE_TECLADO_OK
AAAA:		MOV R0, #0Ah
		SJMP	LE_TECLADO_OK
BBBB:		MOV R0, #0Bh
		SJMP	LE_TECLADO_OK
CCCC:		MOV R0, #0Ch
		SJMP	LE_TECLADO_OK
DDDD:		MOV R0, #0Dh
		SJMP	LE_TECLADO_OK
EEEE:		MOV R0, #0Eh
		SJMP	LE_TECLADO_OK
FFFF:		MOV R0, #0Fh

LE_TECLADO_OK:
		; Incrementa valor lido
		MOV	A, QTD_DIG
		ADD	A, #1
		MOV	QTD_DIG, A

		; Shift nos valores
		MOV	DIG_3, DIG_2
		MOV	DIG_2, DIG_1
		MOV	DIG_1, DIG_0

		MOV	DIG_0, R0
NADA_LIDO:
		; Recebe proximo no DIG0
		RET
;--------------------------------------------
;-------------- SUB-ROTINA INT0 -------------
;--------------------------------------------
EXTERN_0:	CLR 	EA; Desabilita interrupcoes

		SETB	OPT_LIDO; Leu alguma coisa
		MOV	TH0, #0; Zera contador do encoder
		MOV	TL0, #0; Zera contador do encoder
		MOV	S_TICK, #0; Zera contador de segundos (para contar ate 10 segundos)

		SETB	EA; Habilita interrupcoes
		RETI
;--------------------------------------------
;-------------- SUB-ROTINA INT1 -------------
;--------------------------------------------
EXTERN_1:	CLR 	EA; Desabilita interrupcoes
		; Salva valor do R0
		MOV	A, R0
		MOV	R5, A
		ACALL LE_TECLADO

		MOV	A, QTD_DIG
		CJNE	A, #4, CONTINUA_EXTERN_1
		; Alguma senha digitada

		; Testa inicio
		MOV	A, DIG_0
		CJNE	A, #0Dh, TESTA_PAROU
		MOV	A, DIG_1
		CJNE	A, #4h, TESTA_PAROU
		MOV	A, DIG_2
		CJNE	A, #0Fh, TESTA_PAROU
		MOV	A, DIG_3
		CJNE	A, #3h, TESTA_PAROU
		SETB	COMECA_PROG
		MOV	QTD_DIG, #0
		SJMP	CONTINUA_EXTERN_1
TESTA_PAROU:	; Testa parou
		MOV	A, DIG_0
		CJNE	A, #3h, CONTINUA_EXTERN_1
		MOV	A, DIG_1
		CJNE	A, #2h, CONTINUA_EXTERN_1
		MOV	A, DIG_2
		CJNE	A, #1h, CONTINUA_EXTERN_1
		MOV	A, DIG_3
		CJNE	A, #0Eh, CONTINUA_EXTERN_1
		SETB	PARA_PROG
		MOV	QTD_DIG, #0
CONTINUA_EXTERN_1:

		; Volta valor do R0
		MOV	A, R5
		MOV	R0, A
		SETB	EA; Habilita interrupcoes
		RETI
;--------------------------------------------
;-------------- SUB-ROTINA SERIAL -----------
;--------------------------------------------
SERIAL:
		CLR 	EA; Desabilita interrupcoes
		JNB	TI,SERIAL_REC; Verifica se foi recepcao
		CLR	TI; Se foi transmissao, Limpa TI
		SJMP 	SERIAL_FIM
SERIAL_REC:	CLR	RI; Limpa RI
SERIAL_FIM:	SETB	EA; Habilita interrupcoes
		SETB	FLAG_S
		RETI
;------------------------------------------
;-------------- SUB-ROTINAS LCD -----------
;------------------------------------------
; Mostra o valor R2 no LCD
R2_TO_LCD:
		; Mostra valor no LCD
		MOV	A,R2
		ADD	A,#03
		MOVC	A,@A+PC
		CALL	WRITE_TEXT; Escreve no LCD
		RET
TAB:		DB 	'0123456789abcdef'
;-------------------------------------
INIT_LCD:	CLR	RW
		SETB	ENAB
		CLR	RS
		
		; Escreve valor no LCD
		MOV	A, #38h
		MOV	DPTR, #800Dh
		MOVX	@DPTR, A
		
		CLR	ENAB
		LCALL	WAIT_LCD
		;------
		SETB	ENAB
		CLR	RS
		
		; Escreve valor no LCD
		MOV	A, #0Eh
		MOVX	@DPTR, A
		
		CLR	ENAB
		CALL	WAIT_LCD
		;------
		SETB	ENAB
		CLR	RS

		; Escreve valor no LCD
		MOV	A, #06h
		MOVX	@DPTR, A
		
		CLR	ENAB
		LCALL	WAIT_LCD	
		RET
;-----------------
CLEAR_LCD:	CLR	RW
		SETB	ENAB
		CLR	RS

		; Escreve valor no LCD
		MOV	A, #01h
		MOV	DPTR, #800Dh
		MOVX	@DPTR, A
		
		CLR	ENAB
		LCALL	WAIT_LCD
		RET
;-----------------
POS_LCD:	CLR	RW
		SETB	ENAB
		CLR	RS

		; Escreve valor no LCD
		ADD	A, #80h
		MOV	DPTR, #800Dh
		MOVX	@DPTR, A

		CLR	ENAB
		LCALL	WAIT_LCD
		RET
;-----------------
WRITE_TEXT:	CLR	RW
		SETB	ENAB
		SETB	RS

		; Escreve valor no LCD
		MOV	DPTR, #800Dh
		MOVX	@DPTR, A

		CLR	ENAB
		LCALL	WAIT_LCD
		RET
;-----------------
WAIT_LCD:	SETB	RW
		SETB	ENAB
		CLR	RS

		; Escreve valor no LCD
		MOV	A, #0FFh
		MOV	DPTR, #800Dh
		MOVX	@DPTR, A

		; Delay de espera para funcionar em hardware

		CLR	ENAB
		CLR	RW
		RET
		END