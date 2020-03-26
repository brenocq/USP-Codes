#Trabalho 1 - Calculadora
#Breno Cunha Queiroz - 11218991
#Maria Eduarda Kawakami Moreira - 11218751
#23/03/2020

.data
	menu_main: .asciiz "\n\t-----MENU----\n\tEscreva a letra da operação:\n\tM: Memory\n\tC: Calculate\n\t"
	menu_calc: .asciiz "\n\t-----MENU CALCULO----\n\tEscreva o número da operação:\n\t1:  Adição\n\t2:  Subtração\n\t3:  Multiplicação\n\t4:  Divisão\n\t5:  Potenciação\n\t6:  Raiz quadrada\n\t7:  Tabela multiplicação\n\t8:  Fatorial\n\t9:  Fibonacci\n\t10: Sequência Fibonacci\n\t"
	menu_mem: .asciiz "\n\t-----MENU MEMORIA----\n\tEscolha e a memória que você quer consultar:\n\tM1: Memória 1\n\tM2: Memória 2\n\tM3: Memória 3\n\t"
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
	li $v0, 4
	la $a0, menu_calc
	syscall
	
	li $v0, 5
	syscall
	
	beq $a0, 1, addition
	
	j main

memory:
	li $v0, 4
	la $a0, menu_mem
	syscall
	
	j main

#################################################
################## OPERATIONS ###################
#################################################

################### Addition ####################
addition:
	li $v0, 5
	syscall
	
	li $v0, 5
	syscall
	
	j main
	
################# Subtraction ###################

################ Multiplication #################

################## Division #####################

################ Potentiation ###################

################# Square Root ###################

############# Multiplication Table ##############

################## Factorial ####################

################## Fibonacci ####################

############# Fibonacci Sequence ################

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

mult_tab:
	

exit:
	li $v0, 10
	syscall
