		ORG 	0
		MOV	DPTR,#1200H
		MOVX	A,@DPTR
		MOV	30h,A
		SJMP	$
		END