.data
.text
	li $v0, 5
	syscall
	move $t0, $v0
	
	init:
	jal for
	j init
	
for:
	addi $t0, $t0, -1
	
	li $v0, 5
	syscall
	move $t1, $v0
	add $t2, $t2, $t1
	
	beq $t0, $zero, fim
	jr $ra
	
fim:
	li $v0, 1
	add $a0, $zero, $t2
	syscall
	
	li $v0, 10
	syscall