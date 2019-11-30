# Retirar -g
all: main.o auxiliar.o colecao.o
	gcc -g main.o auxiliar.o colecao.o -o programa
main.o: main.c
	gcc -g main.c -c
auxiliar.o: auxiliar.c
	gcc -g auxiliar.c -c
colecao.o: colecao.c
	gcc -g colecao.c -c
run:
	./programa
clean:
	rm -rf programa *.o
