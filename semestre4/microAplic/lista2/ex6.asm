		ORG 	0
		SJMP 	PROGRAM
;--------------------------------------------
		ORG 	3h
		SJMP	EXTERN_0
;--------------------------------------------
		ORG 	13h
		SJMP	EXTERN_1
;--------------------------------------------
		ORG 	1Bh
		SJMP	TIMER_1
;--------------------------------------------
PROGRAM:
BOMBA		EQU	P3.7
		; Interrupcoes
		SETB 	EA ; Habilita interrupções
		SETB 	EX0 ; Habilita a interrupção 0 (Tanque cheio)
		SETB 	IT0 ; Interrupção 0 em borda de descida
		SETB	PX0 ; Interrupcao 0 alta prioridade
		SETB 	EX1 ; Habilita a interrupção 1 (Gatilho da bomba)
		CLR 	IT1 ; Interrupção 1 em nivel baixo
		CLR	PX1 ; Interrupcao 1 baixa prioridade

		; Contador e timer
		; O timer esta sendo utilizado para detectar quando o INT1=1 (muito tempo sem INT1=0)
		MOV	TMOD, #00010101b; Contador por hardware T0 + contador 16 bits
		SETB 	ET1 ; Habilita a interrupção do timer 1 (Parou de abastecer)
		SETB 	TR1; Inicia timer (detectar muito tempo sem INT1=0)
		; Se for mais que 65ms sem abastecer +1 litro entedemos que terminou de abastecer (Depende de saber de informacoes do hardware)
		SETB 	TR0; Inicia contador

		; Inicializacoes
		CLR 	BOMBA; Motor comeca desligado
		ACALL	LIMPA_DISPLAYS

		; Loop
LOOP:		ACALL	ATUALIZA_DISPLAYS
		SJMP 	LOOP

;---------------------------------
LIMPA_DISPLAYS:	; Seleciona todos os display
		MOV	R0,#0FFh
		; Com valor zero
		MOV	R1,#0
		ACALL 	DISPLAY
		RET
;---------------------------------
ATUALIZA_DISPLAYS:
		MOV	A, TL0; Recebe valor em litros ate o momento
		ACALL	CONVERT_BCD; Converte A para BCD
		;---------------
		;---- 4 menos significativos e 4 mais significativos ao mesmo tempo
		;---- Como custa somente 1 real por litro, temos o mesmo numero
		;---------------
		; Mostra display 0 (LSB)
		MOV	R0,#00010001b
		MOV	A,R5
		MOV	R1,A
		ACALL	DISPLAY
		; Mostra display 1 (meio)
		MOV	R0,#00100010b
		MOV	A,R6
		MOV	R1,A
		ACALL	DISPLAY
		; Mostra display 2 (MSB)
		MOV	R0,#01000100b
		MOV	A,R7
		MOV	R1,A
		ACALL	DISPLAY
		; Mostra display 3 (Sempre zero)
		MOV	R0,#10001000b
		MOV	R1,#0
		ACALL	DISPLAY
		RET

;---------------------------------
; Mostra o valor R1 no display R0
; Display R0=00000001 -> LSB
; Display R0=10000000 -> MSB
DISPLAY:	; Seleciona o display
		MOV	P2, R0
		; Mostra valor no display
		MOV	A,R1
		ADD	A,#03
		MOVC	A,@A+PC
		MOV	P1,A
		RET
TAB:		DB 	7Eh,30h,6Dh,79h,33h,5Bh,5Fh,70h,7Fh,7Bh
;-------------------------------- (Tanque cheio)
EXTERN_0:	CLR	EA; Desabilita interrupcoes
		CLR	BOMBA; Desliga a bomba

		SETB	EA; Habilita interrupcoes
		RETI
;-------------------------------- (Gatilho da bomba)
EXTERN_1:	CLR	EA; Desabilita interrupcoes
		JB	BOMBA, BOMBA_LIGADA
		SETB	BOMBA; Liga a bomba
		; Reinicia contagem
		MOV	TL0, #0
		MOV	TH0, #0
		; Limpa displays
		ACALL	LIMPA_DISPLAYS

BOMBA_LIGADA:
		SETB	EA; Habilita interrupcoes
		RETI
;-------------------------------- (Tempo max bomba)
TIMER_1:	CLR	BOMBA; Desliga a bomba
		RETI
;--------------------------------
CONVERT_BCD:	; Convert A to BCD R7 R6 R5
		; R7->MSB
		; R6->Middle
		; R5->LSB
		MOV	B,#10
		DIV	AB      ; floor(number / 10) in A, 1s in B
		MOV	R5,B    ; 1s are now in R1 (bits 3 to 0)
		MOV	B,#10
		DIV	AB      ; floor(number / 100) in A, 10s in B
		MOV	R7,A    ; 100s are now in R0 (bits 3 to 0)
		MOV	R6,B
		RET
		END


