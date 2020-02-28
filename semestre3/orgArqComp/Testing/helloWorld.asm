.data
	newLine:    .asciiz  "\n"
	divisor:    .asciiz  "--------------------\n"
	zeroDouble: .double 0.0

	myMessage:  .asciiz "Hello World!\n"
	character:  .byte   'b'
	number:     .word   42
	pi: 	    .float  3.1415926535
	piD: 	    .double  3.1415926535
	
	num1:	    .word 8
	num2:	    .word 5

.text
	#-------------------------------------------------------------#
	#------------------------ BASIC PRINTING ---------------------#
	#-------------------------------------------------------------#
	# Print string
	li $v0, 4
	la $a0, myMessage
	syscall
	
	# Print char
	li $v0, 4
	la $a0, character
	syscall
	
	#--------- New line ---------#
	li $v0, 4
	la $a0, newLine
	syscall
	# Print integer
	li $v0, 1
	lw $a0, number
	syscall
	
	#--------- New line ---------#
	li $v0, 4
	la $a0, newLine
	syscall
	# Print float
	li $v0, 2
	lwc1 $f12, pi
	syscall
	
	#--------- New line ---------#
	li $v0, 4
	la $a0, newLine
	syscall
	# Print double
	ldc1 $f2, piD
	ldc1 $f0, zeroDouble
	li $v0, 3
	add.d $f12, $f2, $f0
	syscall
	
	#-------------------------------------------------------------#
	#----------------------- BASIC OPERATIONS --------------------#
	#-------------------------------------------------------------#
	# New line
	li $v0, 4
	la $a0, newLine
	syscall
	#---------------- Divisor ---------------#
	li $v0, 4
	la $a0, divisor
	syscall
	#----------------------------- SUM ---------------------------#
	# Calculations
	lw $t1, num1
	lw $t2, num2
	add $t0, $t1, $t2
	# Print
	li $v0, 1
	add $a0, $zero, $t0 
	syscall
	
	#----------------------------- SUB ---------------------------#
	# New line
	li $v0, 4
	la $a0, newLine
	syscall
	# Calculations
	lw $s0, num1
	lw $s1, num2
	sub $t0, $s0, $s1
	# Print
	li $v0, 1
	move $a0, $t0 
	syscall
	
	#----------------------------- MUL ---------------------------#
	# New line
	li $v0, 4
	la $a0, newLine
	syscall
	# Calculations
	addi $s0, $zero, 2 # Must be a number?
	addi $s1, $zero, 20
	mul $t0, $s0, $s1
	# Print
	li $v0, 1
	move $a0, $t0 
	syscall
	
	#----------------------------- MULT ---------------------------#
	# New line
	li $v0, 4
	la $a0, newLine
	syscall
	# Calculations
	addi $t0, $zero, 2000
	addi $t1, $zero, 10
	mult $t0, $t1
	mflo $s0
	# Print
	li $v0, 1
	move $a0, $s0 
	syscall
	
	#------------------------------ SLL ---------------------------#
	# New line
	li $v0, 4
	la $a0, newLine
	syscall
	# Calculations
	addi $s0, $zero, 4
	sll $t0, $s0, 2
	# Print
	li $v0, 1
	move $a0, $t0 
	syscall
	
	#--------------------------- DIV INT --------------------------#
	# New line
	li $v0, 4
	la $a0, newLine
	syscall
	#---------------- Divisor ---------------#
	li $v0, 4
	la $a0, divisor
	syscall
	
	# Calculations
	addi $t0, $zero, 15
	addi $t1, $zero, 5
	div $s0, $t0, $t2
	div $s1, $t0, 3
	
	addi $t0, $zero, 16
	addi $t1, $zero, 5
	div $t0, $t1
	mflo $s2 # Quotient
	mfhi $s3 # Remainder
	
	# Print (div $s0, $t0, $t2)
	li $v0, 1
	move $a0, $s0 
	syscall
	# New line
	li $v0, 4
	la $a0, newLine
	syscall
	# Print (div $s1, $t0, 3)
	li $v0, 1
	move $a0, $s1 
	syscall
	# New line
	li $v0, 4
	la $a0, newLine
	syscall
	# Print (mflo $s2) (quotient)
	li $v0, 1
	move $a0, $s2 
	syscall
	# New line
	li $v0, 4
	la $a0, newLine
	syscall
	# Print (mflo $s2) (remainder)
	li $v0, 1
	move $a0, $s3 
	syscall
