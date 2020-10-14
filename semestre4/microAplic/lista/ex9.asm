		ORG 	0h
OBSTACLE	EQU	20h.0; Flag indicando se objeto foi detectado
TURN		EQU	20h.1; Flag indicando para qual lado virar
		SJMP	PROG
		ORG	3h
		SJMP	EXTERN_0
;--------------------------------------------
PROG:		SETB 	EA ; Habilita interrupções
		SETB 	EX0 ; Habilita a interrupção zero
		CLR 	IT0 ; Ativado em nivel logico baixo (enquanto o sensor detecta obstaculo)
		CLR	OBSTACLE ; Limpa flag de obstaculo detectado
		CLR	TURN ; Virar para direita na primeira vez

		SETB	P1.0 ; Liga alimentacao do motor da roda esquerda
		SETB	P1.2 ; Liga alimentacao do motor da roda direita

LOOP:		SETB 	EX0 ; Habilita interrupção 0
		; Move para frente ate detectar objeto
		SETB	P1.0
		SETB	P1.1
WAIT:		JB	OBSTACLE, DETECTED ; Espera ate detectar obstaculo
		SJMP	WAIT
DETECTED:	; Obstaculo detectado
		CLR 	EX0 ; Desabilita interrupção 0
		CLR	OBSTACLE ; Limpa flag de deteccao de obstaculo
		; Move para tras
		CLR	P1.0
		CLR	P1.1
		CALL	DELAY_2S
		JB	TURN, ESQUERDA
		; Vira para direita
		SETB	P1.0
		CLR	P1.1
		CALL	DELAY_2S
		SETB	TURN ; Prox vez para esquerda
		SJMP 	LOOP
ESQUERDA:	; Vira para esquerda
		CLR	P1.0
		SETB	P1.1
		CALL	DELAY_2S
		CLR	TURN ; Prox vez para direita
		SJMP 	LOOP

;--------------------------------------------
EXTERN_0:	SETB	OBSTACLE
		RETI
;--------------------------------------------
DELAY_2S:	; Delay de 2 segundos
		MOV	R5, #01Ch
		MOV	R6, #0EDh
		MOV	R7, #0E0h
		NOP
		DJNZ	R7, $
		DJNZ	R6, $-5
		DJNZ	R5, $-9
		MOV	R7, #0DDh
		DJNZ	R7, $
		RET
		END