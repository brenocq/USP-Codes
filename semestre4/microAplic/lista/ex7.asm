		ORG 0h
		SJMP	PROG
		ORG 3h
		SJMP	EXTERN_0
;-------------------------------------
PROG:		MOV	TMOD, #00100001b ; Configura timer entre pulsos(T0) de descida e timer da serial (T1)
		SETB	EA ; Habilita interrupcoes
		SETB	EX0 ; Habilita interrupcao do extern 0
		SETB	IT0 ; Configura interrupcao em borda de descida

		; Configurando comunicacao com 4800 (208us)
		MOV 	SCON,#01000000b ; Modo 1 de comunicacao
		MOV 	PCON, #10000000b; K=2
		MOV 	TH1,#244
		MOV 	TL1,#244
		; Configura timer
		;MOV 	TMOD, #20h ;Timer 1 configurado no modo de recarga automática
		SETB 	TR1 ; Dispara Temporizador da serial
		SETB 	TR0 ; Dispara contador de pulsos

LOOP:		;------ Espera um tempo para ler os pulsos -------
		CALL DELAY
		
		;---------- Envia frequencia pela serial ---------
		CLR	EA ; Desabilita interrupcoes
		; Envia primeira parte dos 16 bits
		MOV	A,R0
		MOV 	SBUF,A ; Inicia a transmissão de um byte
        	JNB 	TI,$ ; Aguarda fim da transmissão
        	CLR 	TI ; Prepara para nova transmissao

        	; Envia segunda parte dos 16 bits
        	MOV	A,R1
		MOV 	SBUF,A ; Inicia a transmissão de um byte
        	JNB 	TI,$ ; Aguarda fim da transmissão
        	CLR 	TI ; Prepara para nova transmissao

		SETB	EA ; Habilita interrupcoes
        	SJMP 	LOOP ; Retorna para o loop principal
        	
;-------------------------------------
EXTERN_0:	CLR	EA ; Desabilita interrupcoes
		; Move pulsos detectados para os registradores
		MOV	R0, TL0
		MOV	R1, TH0
		;OBS: Para calcular a frequencia em Hz a partir da saida da serial: 1/(pulsos*1.0851*10^-6)
		
		; Zera timer para contar ate a proxima borda de descida
		MOV	TL0, #0
		MOV	TH0, #0
		SETB	EA ; Habilita interrupcoes
		RETI
;-------------------------------------
DELAY:		; Espera 10ms para ler os pulsos
		; Comentado para facilitar os testes
		;MOV	R6, #015h
		;MOV	R7, #0ECh
		;NOP
		;DJNZ	R7, $
		;DJNZ	R6, $-5
		NOP
		NOP
		NOP
		RET
		END