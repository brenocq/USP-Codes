		ORG 0
		MOV P1,#00 ; Apagando todos os LED’s
LOOP: 		ACALL DELAY ; Delay de 1s
		JB P3.5, PISCA1 ; Verificando se CH1 está fechada
		JB P3.6, PISCA2 ; Verificando se CH2 está fechada
		JB P3.7, PISCA3 ; Verificando se CH3 está fechada
		SJMP LOOP ; Retornar para continuar a operação

DELAY:		MOV R1, #3E5h ;1 ciclo (997)
DELAY_LOOP:	MOV R0, #1F4h ;1 ciclo (500)
		DJNZ R0, $ ;2 ciclos
		DJNZ R1, DELAY_LOOP ;2 ciclos
		RET ; Continua o loop

PISCA1:		MOV P1.0, C ; Pisca o LED 1
		CLR P1.1 ; Desliga o LED 2
		CPL C ; Inverte o carry
		SJMP LOOP ; Retorna para o loop

PISCA2:		MOV P1.1, C ; Pisca o LED 2
		CLR P1.0 ; Desliga o LED 1
		CPL C ; Inverte o carry
		SJMP LOOP ; Retorna para o loop

PISCA3:		MOV P1.0, C ; Pisca o LED 1
		CPL C ; Inverte o carry
		MOV P1.1, C ; Pisca o LED 2 invertido
		SJMP LOOP ; Retorna para o loop
		END

