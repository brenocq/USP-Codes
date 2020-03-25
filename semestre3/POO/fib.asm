.data
	str1: .asciiz "\n\tDigite um numero:"
.text
.globl main
main:
	# Pede um numero
	li $v0, 4
	la $a0, str1
	syscall
	
	li $v0, 5
	syscall
	addi $a0, $v0, 0
	
	# Roda o fatorial
	jal fib
	
	addi $a0, $v0, 0
	li $v0, 1
	syscall
	
	li $v0, 10
	syscall
	
fib:
	sub $sp, $sp, 8 # Ajusta stack pra dois items
	sw $ra, 4($sp) # Guarda endereço de retorno
	sw $a0, 0($sp) # Gurarda argumento n
	
	slti $t0, $a0, 2 # Testa se fib<2
	beq $t0, $zero, L1 # Se fib>=2, chama L1, senão, retorna 1
	li $v0, 1 # Retorna 1
	
	add $sp, $sp, 8 # Libera o espaço da stack antes de retornar
	jr $ra # Retorna
	
L1:
	# Recupera argumento passado
	lw $a0, 0($sp)

	sub $a0, $a0, 1 # Nova chamada com (n-1)
	jal fib # chama fibonatti (n-1)
	add $t0, $v0, $zero
	
	# Recupera argumento passado
	lw $a0, 0($sp)
	
	sub $a0, $a0, 2 # Nova chamada com (n-2)
	jal fib # chama fibonatti (n-2)
	add $t1, $v0, $zero
	
	# Recupera endereço de retorno
	lw $ra, 4($sp)
	
	add $sp, $sp, 8 # Libera o espaço da stack antes de retornar
	
	add $v0, $t0, $t1  # Calcula n^exp * n
	jr $ra