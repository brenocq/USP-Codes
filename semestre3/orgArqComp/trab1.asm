#Trabalho 1 - Calculadora
#Breno Cunha Queiroz - 11218991
#Maria Eduarda Kawakami Moreira - 11218751
#23/03/2020

.data
	menu_main: .asciiz "\n\n\t-----MENU----\n\tEscreva a letra da operação:\n\tM: Memory\n\tC: Calculate\n\t"
	menu_calc: .asciiz "\n\n\t-----MENU CALCULO----\n\tEscreva o número da operação:\n\t1:  Adição\n\t2:  Subtração\n\t3:  Multiplicação\n\t4:  Divisão\n\t5:  Potenciação\n\t6:  Raiz quadrada\n\t7:  Tabela multiplicação\n\t8:  Fatorial\n\t9:  Fibonacci\n\t10: Sequência de Fibonacci\n\t"
	menu_mem: .asciiz "\n\n\t-----MENU MEMORIA----\n\tEscolha a memória que você quer consultar:\n\tM1: Memória 1\n\tM2: Memória 2\n\tM3: Memória 3\n\t"
	addition_header: .asciiz "\n\t-----ADIÇÃO----\n"
	subtraction_header: .asciiz "\n\t-----SUBTRAÇÃO----\n"
	multiplication_header: .asciiz "\n\t-----MULTIPLICAÇÃO----\n"
	division_header: .asciiz "\n\t-----DIVISÃO----\n"
	potentiation_header: .asciiz "\n\t-----POTENCIAÇÃO----\n"
	square_root_header: .asciiz "\n\t-----RAIZ QUADRADA----\n"
	mult_table_header: .asciiz "\n\t-----TABELA MULTIPLICAÇÃO----\n"
	factorial_header: .asciiz "\n\t-----FATORIAL----\n"
	fibonacci_header: .asciiz "\n\t-----FIBONACCI----\n"
	fibonacci_sequence_header: .asciiz "\n\t-----SEQUÊNCIA DE FIBONACCI----\n"
	first_num: .asciiz "\tPrimeiro número:"
	second_num: .asciiz "\tSegundo número:"
	result: .asciiz "\tResultado:"
	m1_result: .asciiz "\n\tValor de M1:"
	m2_result: .asciiz "\n\tValor de M2:"
	m3_result: .asciiz "\n\tValor de M3:"
	memory_selected: .space 3
.text

.globl main
main:
	li $v0, 4
	la $a0, menu_main
	syscall
	
	li $v0, 12
	syscall
	
	addi $a0, $v0, 0
	
	#choose M or C
	li $t0, 'C'
	beq $a0, $t0, calculate
	li $t0, 'M'
	beq $a0, $t0, memory
	
	# Exit program
	j exit
	
#################################################
################## SEC MENUS ####################
#################################################
calculate:
	# Show menu
	li $v0, 4
	la $a0, menu_calc
	syscall
	
	# Read option
	li $v0, 5
	syscall
	
	beq $v0, 1, addition
	beq $v0, 2, subtraction
	beq $v0, 3, multiplication
	beq $v0, 4, division
	
	j main

memory:
	# Show menu
	li $v0, 4
	la $a0, menu_mem
	syscall
	
	# Read option
	li $v0, 8
	la $a0, memory_selected
	li $a1, 3
	syscall
	
	# Load second char to t0
	la $a0, memory_selected
	# Load char 1,2,3 to compare
	lb $t0, 1($a0)
        li $t1, '1'
        li $t2, '2'
        li $t3, '3'
	
	# Compare input with each option
	beq $t0, $t1, show_m1
	beq $t0, $t2, show_m2
	beq $t0, $t3, show_m3
	
	j main

#################################################
################## OPERATIONS ###################
#################################################

################### Addition ####################
addition:
	# Show header
	li $v0, 4
	la $a0, addition_header
	syscall
	
	# Read first num
	li $v0, 4
	la $a0, first_num
	syscall
	
	li $v0, 5
	syscall
	
	move $t0, $v0
	# Read second num
	li $v0, 4
	la $a0, second_num
	syscall
	
	li $v0, 5
	syscall
	
	move $t1, $v0
	
	# Calculate result
	add $t2, $t0, $t1
	
	# Show result
	li $v0, 4
	la $a0, result
	syscall
	
	li $v0, 1
	move $a0, $t2
	syscall
	
	# Save result memory
	jal shift_memory
	move $s5, $t2
	
	j main
	
################# Subtraction ###################
subtraction:
	# Show header
	li $v0, 4
	la $a0, subtraction_header
	syscall
	
	# Read first num
	li $v0, 4
	la $a0, first_num
	syscall
	
	li $v0, 5
	syscall
	
	move $t0, $v0
	# Read second num
	li $v0, 4
	la $a0, second_num
	syscall
	
	li $v0, 5
	syscall
	
	move $t1, $v0
	
	# Calculate result
	sub $t2, $t0, $t1
	
	# Show result
	li $v0, 4
	la $a0, result
	syscall
	
	li $v0, 1
	move $a0, $t2
	syscall
	
	# Save result memory
	jal shift_memory
	move $s5, $t2
	
	j main
################ Multiplication #################
multiplication:
	# Show header
	li $v0, 4
	la $a0, multiplication_header
	syscall
	
	# Read first num
	li $v0, 4
	la $a0, first_num
	syscall
	
	li $v0, 5
	syscall
	
	move $t0, $v0
	# Read second num
	li $v0, 4
	la $a0, second_num
	syscall
	
	li $v0, 5
	syscall
	
	move $t1, $v0
	
	# Calculate result
	mul $t2, $t0, $t1
	
	# Show result
	li $v0, 4
	la $a0, result
	syscall
	
	li $v0, 1
	move $a0, $t2
	syscall
	
	# Save result memory
	jal shift_memory
	move $s5, $t2
	
	j main
################## Division #####################
division:
	# Show header
	li $v0, 4
	la $a0, division_header
	syscall
	
	# Read first num
	li $v0, 4
	la $a0, first_num
	syscall
	
	li $v0, 5
	syscall
	
	move $t0, $v0
	# Read second num
	li $v0, 4
	la $a0, second_num
	syscall
	
	li $v0, 5
	syscall
	
	move $t1, $v0
	
	# Calculate result
	div $t2, $t0, $t1
	
	# Show result
	li $v0, 4
	la $a0, result
	syscall
	
	li $v0, 1
	move $a0, $t2
	syscall
	
	# Save result memory
	jal shift_memory
	move $s5, $t2
	
	j main
	
################ Potentiation ###################

################# Square Root ###################

############# Multiplication Table ##############

################## Factorial ####################

fact:
	sub $sp, $sp, 8 
 	sw $ra, 4($sp) #store $ra
 	sw $a0, 0($sp) #store n
 	slti $t0, $a0, 1 #$t0 = 1 if n < 1
 	beq $t0, $zero, fact_rec #if n >= 1, call fact_rec
 	li $v0, 1 #if n < 1 return 1 - base case
 	add $sp, $sp, 8 # free stack
 	jr $ra
 	
fact_rec:
 	sub $a0, $a0, 1 #n-1
 	jal fact
 	lw $a0, 0($sp) #restore n
 	lw $ra, 4($sp) #restore $ra
 	add $sp, $sp, 8 #free stack
 	mul $v0, $a0, $v0 #return n * fact(n-1)
 	jr $ra
################## Fibonacci ####################
fib:
	sub $sp, $sp, 12
	sw $ra, 4($sp) 
	sw $a0, 0($sp) #save n
	slti $t0, $a0, 3 # $t0 = 1 if n < 3
 	beq $t0, $zero, fib_rec #if n >= 3, call fib_rec
	li $v0, 1 #if n < 3 return 1 #base case
	add $sp, $sp, 12
	jr $ra

fib_rec:
	sw $ra, 4($sp) #save $ra
	sw $a0, 0($sp) #save n for fib(n-2)
	sub $a0, $a0, 1	#n-1
	jal fib
	lw $a0, 0($sp) #restore n
	lw $ra, 4($sp) #restore $ra
	sw $v0, 8($sp) #save return fib(n-1)
	sub $a0, $a0, 2 #n-2	
	jal fib
	lw $t0, 8($sp) #restore return fib(n-1)
	add $v0, $t0, $v0 #return fib(n-1) + fib(n-2)
	lw $ra, 4($sp) #restore $ra
	add $sp, $sp, 12 #tear down stack
	jr $ra		
############# Fibonacci Sequence ################

#################################################
################# SHOW MEMORY ###################
#################################################
show_m1:
	# Show header
	li $v0, 4
	la $a0, m1_result
	syscall
	
	# Show value
	li $v0, 1
	move $a0, $s5
	syscall
	
	j memory
	
show_m2:
	# Show header
	li $v0, 4
	la $a0, m2_result
	syscall
	
	# Show value
	li $v0, 1
	move $a0, $s6
	syscall
	
	j memory
	
show_m3:
	# Show header
	li $v0, 4
	la $a0, m3_result
	syscall
	
	# Show value
	li $v0, 1
	move $a0, $s7
	syscall
	
	j memory

#################################################
################# AUXILIARIES ###################
#################################################
shift_memory:
	move $s7, $s6
	move $s6, $s5
	add $s5, $zero, $zero

	jr $ra
	
exit:
	li $v0, 10
	syscall
