.data
	newLine:    .asciiz  "\n"
	test:       .asciiz  "test\n"
	number:     .word    42

.text
	li $v0, 5
	syscall
	addi $t0, $v0
	
	#------- Print integer ------#
	li $v0, 1
	lw $a0, number
	syscall
	
	#--------- New line ---------#
	li $v0, 4
	la $a0, newLine
	syscall
	#--------- Test ---------#
	li $v0, 4
	la $a0, test
	syscall
	#---------- The end ---------#
	li $v0, 10
	syscall