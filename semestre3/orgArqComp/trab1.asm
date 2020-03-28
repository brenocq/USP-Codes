#Trabalho 1 - Calculadora
#Breno Cunha Queiroz - 11218991
#Maria Eduarda Kawakami Moreira - 11218751
#23/03/2020

.data
	menu_main: .asciiz "\n\n\t-----MENU----\n\tEscreva a letra da operação:\n\tM: Memória\n\tC: Cálculo\n\t"
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
	num: .asciiz "\tNúmero: "
	first_num: .asciiz "\tPrimeiro número:"
	second_num: .asciiz "\tSegundo número:"
	base: .asciiz "\tBase:"
	expoent: .asciiz "\tExpoente:"
	not_natural: .asciiz "Raiz quadrada não natural"
	first_num_fib: .asciiz "\tPrimeiro numero(menor):"
	second_num_fib: .asciiz "\tSegundo numero(maior):"
	result: .asciiz "\tResultado:"
	m1_result: .asciiz "\n\tValor de M1:"
	m2_result: .asciiz "\n\tValor de M2:"
	m3_result: .asciiz "\n\tValor de M3:"
	empty_memory: .asciiz "Nenhum valor salvo"
	memory_selected: .space 3
.text

.globl main
init:
	jal init_empty_memory
	j main

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
	beq $v0, 5, potentiation_main
	beq $v0, 6, square_root_main
	beq $v0, 7, mult_table
	beq $v0, 8, fact_main
	beq $v0, 9, fib_main
	beq $v0, 10, fib_seq_main
	# Return to main
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
	# Return to main
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
	# Return to main
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
	# Return to main
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
	# Return to main
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
	# Return to main
	j main
	
################ Potentiation ###################
potentiation_main:
	# Show header
        li $v0, 4
        la $a0, potentiation_header
        syscall

        # Read base
        li $v0, 4
        la $a0, base
        syscall

        li $v0, 5
        syscall

        move $t0, $v0

        # Read expoent
        li $v0, 4
        la $a0, expoent
        syscall

        li $v0, 5
        syscall

        move $t1, $v0
	
	jal potentiation
	
	# Show result
	li $v0, 4
	la $a0, result
	syscall
	
	# Show number
	li $v0, 1
	la $a0, ($t2)
	syscall
	
	# Save result memory
	jal shift_memory
	move $s5, $a0
	# Return to main
	j main
	
potentiation:
	sub $sp, $sp, 8
	sw $ra, 4($sp)
	sub $t1, $t1, 1
	beq $t1, 0, potentiation_return
	jal potentiation
	lw $t3, 0($sp)
	mul $t2, $t0, $t3
	addi $sp, $sp, 8
	sw $t2, 0($sp)
	lw $t3, 4($sp)
	jr $t3
	
potentiation_return:
	sw $t0, 0($sp)
	lw $ra, 4($sp)
	jr $ra

################# Square Root ###################
square_root_main:
	# Show header
	li $v0, 4
	la $a0, square_root_header
	syscall
	
	# Ask for number
	li $v0, 4
        la $a0, num
        syscall
        
        # Get number
        li $v0, 5
        syscall
        
        jal square_root
        move $t1, $v0
        
        # Show "result:"
	li $v0, 4
	la $a0, result
	syscall
        
        # Show result number/not natural
        bne $t1, -1, square_root_display_natural# If natural
        beq $t1, -1, square_root_display_not_natural# If not natural
        
        square_root_display_natural:
       		# Display number
		li $v0, 1
		move $a0, $t1
		syscall
		
		# Save result memory
		jal shift_memory
		move $s5, $a0
		j square_root_display_end
	square_root_display_not_natural:
		# Display not natural
		li $v0, 4
		la $a0, not_natural
		syscall
		j square_root_display_end
	
	square_root_display_end:
        
	# Return to main
	j main

square_root:
        # Init ariables
        add $t0, $v0, $zero   # goal x*x
        
        addi $t1, $zero, 1    
        sll $t1, $t1, 15       # bit mask offset (0000 0000 0000 0000 1000 0000 0000 0000)
     
        add $t2, $zero, $zero # x
        add $t3, $zero, $zero # x*x
        
        square_root_while:
        	# Test mask
        	add $t2, $t2, $t1 # t2=x+mask
        	mul $t3, $t2, $t2 # t3=t2*t2
        	
        	ble $t3, $t0, square_root_continue # If x*x>goal
        		sub $t2, $t2, $t1 # t2=x-mask
        	square_root_continue:
        	beq $t3, $t0, square_root_end # If x*x==goal
        	
		srl $t1, $t1, 1
		beqz $t1, square_root_end # If x*x==goal not found
		
        	j square_root_while
        square_root_end:
        
	bnez $t1, square_root_natural # If square root not natural
		addi, $t2, $zero, -1
	square_root_natural:
     
     	move $v0, $t2
     	
        jr $ra
############# Multiplication Table ##############

mult_table:
	#show header
        li $v0, 4
        la $a0, mult_table
        syscall

        #ask for number
        li $v0, 4
        la $a0, num
        syscall
	
	sub $sp, $sp, 8
	sw $ra, 4($sp) #store $ra
	sw $a0, 0($sp) #store n
	
	li $t1, 10 #counter
	
	slti $t0, $t1, 1 #t0 = 1 if counter < 1



################## Factorial ####################

fact_main:
	#show header
	li $v0, 4
	la $a0, factorial_header
	syscall
	
	#ask for number
	li $v0, 4
        la $a0, num
        syscall
	
	jal fact
	
	# Show result
	li $v0, 4
	la $a0, result
	syscall
	
	addi $a0, $v0, 0
	
	li $v0, 1
	syscall
	
	# Save result memory
	jal shift_memory
	move $s5, $a0
	# Return to main
	j main

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

fib_main:
	
	#show header
        li $v0, 4
        la $a0, fibonacci_header
        syscall

        #ask for number
        li $v0, 4
        la $a0, num
        syscall
        
        jal fib
	
	# Show result
	li $v0, 4
	la $a0, result
	syscall
	
	addi $a0, $v0, 0
	
	li $v0, 1
	syscall
	
	# Save result memory
	jal shift_memory
	move $s5, $a0
	# Return to main
	j main

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
fib_seq_main:
	# Show header
	li $v0, 4
	la $a0, fibonacci_sequence_header
	syscall
	
	# Ask first num
	li $v0, 4
	la $a0, first_num_fib
	syscall
	
	# Get first num
	li $v0, 5
	syscall
	move $t0, $v0
	
	move $t0, $v0
	# Ask second num
	li $v0, 4
	la $a0, second_num_fib
	syscall
	
	# Get second num
	li $v0, 5
	syscall
	move $t1, $v0
	
	# Nothing to save to memory
	# Return to main
	j main

#################################################
################# SHOW MEMORY ###################
#################################################
show_m1:
	# Show header
	li $v0, 4
	la $a0, m1_result
	syscall
	
	beq $s5, -1, show_m1_empty #If not empty
		# Show value
		li $v0, 1
		move $a0, $s5
		syscall
		j show_m1_end
	show_m1_empty: #If empty
		# Show empty
		li $v0, 4
		la $a0, empty_memory
		syscall
	show_m1_end:
	
	j memory
	
show_m2:
	# Show header
	li $v0, 4
	la $a0, m2_result
	syscall
	beq $s6, -1, show_m2_empty #If not empty
		# Show value
		li $v0, 1
		move $a0, $s6
		syscall
		j show_m2_end
	show_m2_empty: #If empty
		# Show empty
		li $v0, 4
		la $a0, empty_memory
		syscall
	show_m2_end:
	
	j memory
	
show_m3:
	# Show header
	li $v0, 4
	la $a0, m3_result
	syscall
	
	beq $s6, -1, show_m3_empty #If not empty
		# Show value
		li $v0, 1
		move $a0, $s7
		syscall
		j show_m3_end
	show_m3_empty: #If empty
		# Show empty
		li $v0, 4
		la $a0, empty_memory
		syscall
	show_m3_end:
	
	j memory

#################################################
################# AUXILIARIES ###################
#################################################
init_empty_memory:
	addi $s5, $zero, -1# M1
	addi $s6, $zero, -1# M2
	addi $s7, $zero, -1# M3
	
	jr $ra
	
shift_memory:
	move $s7, $s6
	move $s6, $s5
	add $s5, $zero, $zero

	jr $ra
	
exit:
	li $v0, 10
	syscall
