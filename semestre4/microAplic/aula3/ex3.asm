		ORG 0
		SJMP PROG
;--------------------------------------------
		ORG 0003
		SJMP EXTERN_0
;--------------------------------------------
PROG:		SETB EX0 ; Habilita a interrupção zero
		SETB IT0 ; Ativado em descida de borda
		SETB PX0 ; Interrupção zero de alta prioridade
		SETB EA ; Habilita interrupções

		MOV P2, #0 ; Limpa saida P2
		SETB P2.1 ; Aciona o motor (horario)
		CLR P2.7 ; Aciona o motor (horario)
		CLR C ; Define estado como zero
		SJMP $

;--------------------------------------------
DELAY_5S:	MOV R1, #9C0h ;1 ciclo (2496)
DELAY_LOOP:	MOV R0, #3E8h ;1 ciclo (1000)
		DJNZ R0, $ ;2 ciclos
		DJNZ R1, DELAY_LOOP ;2 ciclos
		RET ; Continua o loop

;--------------------------------------------
EXTERN_0:	CLR EA ; Desabilita interrupcoes para nao interromper
		CLR P2.1 ; Para a esteira
		CLR P2.7 ; Para a esteira
		JB C, EXTERN_0_ST1; Vai para o estado atual

		; Estado zero
		ACALL DELAY_5S ; Espera 5 segundos
		CLR P2.1 ; Inverte sentido do motor (anti-horario)
		SETB P2.7 ; Inverte sentido do motor (anti-horario)
		SETB C ; Define estado como um

		SETB EA ; Habilita interrupcoes novamente
		RETI

		; Estado um
EXTERN_0_ST1:	ACALL DELAY_5S ; Espera 10 segundos
		ACALL DELAY_5S
		SETB P2.1 ; Aciona o motor (horario)
		CLR P2.7 ; Aciona o motor (horario)
		CLR C ; Define estado como zero

		SETB EA ; Habilita interrupcoes novamente
		RETI		
		END