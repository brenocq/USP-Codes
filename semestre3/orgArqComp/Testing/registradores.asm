.data
	var1 .word 1
.text
main:
	lw $t0, var1
	li $t1 2
	add $t1, $t1, $t0
	sw $t1 var1

fim:
	li $v0, 10
	syscall