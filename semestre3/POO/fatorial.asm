.data
	strl: .asciiz "\n\tDigite um valor:"
.text
.globl main
main:
	# Pede o número
	li $v0, 4
	la $a0, strl
	syscall
	# Le o numero inteiro
	li $v0, 5
	syscall
	addi $a0, $v0, 0
	
	# Roda o fatorial
	jal fact
	
	# Mostra o fatorial
	addi $a0, $v0, 0
	li $v0, 1
	syscall
	
	# Termina o programa
	li $v0, 10
	syscall
	
fact:
	sub $sp, $sp, 8 # Ajusta stack pra dois items
	sw $ra, 4($sp) # Guarda endereço de retorno
	sw $a0, 0($sp) # Gurarda argumento n
	
	slti $t0, $a0, 1 # Testa se n<1
	beq $t0, $zero, L1 # Se n>=1, chama L1, senão, retorna1
	li $v0, 1 # Retorna 1
	
	add $sp, $sp, 8 # Libera o espaço da stack antes de retornar
	jr $ra # Retorna
	
L1:
	sub $a0, $a0, 1 # Nova chamada com (n-1)
	jal fact # chama fatorial (n-1)
	
	# Ponto de retorno da chamada recursiva
	lw $a0, 0($sp) # Recupera argumento passado
	lw $ra, 4($sp) # Recupera endereço de retorno
	add $sp, $sp, 8 # Libera o espaço da stack
	
	mul $v0, $a0, $v0 # Calcula n*fact (n-1)
	jr $ra