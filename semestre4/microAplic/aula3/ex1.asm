		ORG 0
		MOV P1,#00 ; Apagando todos os LED’s
LOOP: 		MOV C,P3.5 ; Colocando o Status da CH1 no Carry
		MOV P1.0,C ; Transportando para o LED 1
		MOV C,P3.6 ; Colocando o Status da CH2 no Carry
		MOV P1.1,C ; Transportando para o LED 2
		MOV C,P3.7 ; Colocando o Status da CH3 no Carry
		MOV P1.2,C ; Transportando para o LED 3
		SJMP LOOP ; Retornar para continuar a operação
		END