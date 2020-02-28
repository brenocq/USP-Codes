.data
	message: .asciiz "Testing...\nNew line.\n"
.text
	main:
		jal displayMessage
		
		addi $a1,$zero, 50
		addi $a2,$zero, 100
		jal addNumbers
		li $v0, 1
		addi $a0, $v1, 0
		syscall
		
	
	# Program is done
	li $v0, 10
	syscall
	
	displayMessage:
		li $v0, 4
		la $a0, message
		syscall
		
		# Return to caller
		jr $ra
		
	addNumbers:
		add $v1, $a1, $a2
		jr $ra
		
	# Continue from here: https://www.youtube.com/watch?v=3napwKvocSU&list=PL5b07qlmA3P6zUdDf-o97ddfpvPFuNa5A&index=17
		