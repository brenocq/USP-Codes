#Trabalho 1 - Calculadora
#Breno Cunha Queiroz - 11219551
#Maria Eduarda Kawakami Moreira - 11218751
#23/03/2020

.data
	operation .asciiz "\n\tWrite the number of the operation:\n\t1: Addition\n\t2:Subtraction\n\t3: Multiplication\n\t4: Division\n\t5: Potentiation\n\t6: Square Root\n\t7: Multiplication Table\n\t8: Factorial\n\t9:Fibonacci\n\t10: Fibonacci Sequence\n\t"
	menu_option .asciiz "\n\tWrite the letter of the procedure:\n\tM: Memory\n\tC: Calculate\n\t"
	menu .asciiz "\n\t-----MENU----\n\t"
.text

.globl main
main:
	li $v0, 4
	la $a0, menu
	syscall
	
	li $v0, 4
	la $a0, menu_option
	syscall
	
	li $v0, 5
	syscall
	
	addi $a0, $v0, 0
	#choose M or C, idk yet how to do that
	#breno, isso eu tava só testando, pode ignorar e fazer certo KKKK
	li $t0, 'C'
	beq $a0, $t0, calculate
	li $t0, 'M'
	beq $a0, $t0, memory
	#switch for each operation, i think i know how
	
	

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
