		ORG 0h
		SJMP	PROG
;-------------------------------------
PROG:
		; Subtrair para ler 10 vezes
		MOV	R0,#10
		MOV	R1,#0; Contador de numeros impares
		MOV	R2,#0; Contador de numeros pared

		; Configura serial
		MOV 	TMOD,#20h ; Timer 1 no modo 2, controle por software
		MOV 	SCON,#01000000b ; Modo 1 de comunicacao
		MOV 	PCON, #10000000b; K=2


		MOV 	DPTR, #TAB ; Aponta DPTR para a tabela
LOOP:		MOV 	A, #0x00
    		MOVC 	A, @A+DPTR
    		; B armazena o valor da tabela
		MOV	B, A

		; Checa par ou impar
            	RRC 	A ; Rotaciona para a direita para o carry
            	JC 	IMPAR ; Bit com 1 ou 0 (impar/par)
            	SJMP 	PAR
;----------
IMPAR: 		MOV	P2,B ; Envia numero para P2
		INC	R1 ; Incrementa contator
		; Envia pela serial
		; Configurando comunicacao com 4800
		MOV 	TH1,#244
		MOV 	TL1,#244
		SETB 	TR1 ; Dispara temporizador da serial

		; Envia numero pela serial
		MOV 	SBUF,B ; Inicia a transmissão de um byte
        	JNB 	TI,$ ; Aguarda fim da transmissão
        	CLR 	TI ; Prepara para nova transmissao

		CLR	TR1 ; Para temporizador da serial
		SJMP	FIM
;----------
PAR:  		MOV	P1,B ; Envia numero para P1
		INC	R2 ; Incrementa contator
		; Envia pela serial
		; Configurando comunicacao com 9600
		MOV 	TH1,#250
		MOV 	TL1,#250
		SETB 	TR1 ; Dispara temporizador da serial

		; Envia numero pela serial
		MOV 	SBUF,B ; Inicia a transmissão de um byte
        	JNB 	TI,$ ; Aguarda fim da transmissão
        	CLR 	TI ; Prepara para nova transmissao

		CLR	TR1 ; Para temporizador da serial
;----------
FIM:		INC 	DPTR
		DJNZ	R0, LOOP ; Executa 10 vezes
		; Escreve quantidade da RAM externa
		; Qtd pares
		MOV	DPTR,#2030H
		MOV	A, R2
		MOVX	@DPTR, A
		; Qtd impares
		MOV	DPTR,#2031H
		MOV	A, R1
		MOVX	@DPTR, A

        	SJMP 	$ ; Fim

TAB:		DB	01h, 02h, 03h, 04h, 0Ah, 0Bh, 20h, 21h, 01h, 03h
		END