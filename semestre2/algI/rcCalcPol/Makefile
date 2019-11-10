all: build

run: build
	./prog

build: pilha.o arvoreBinaria.o main.o

main.o: main.c
	@g++ -g main.c -Wall -o prog pilha.o arvoreBinaria.o

pilha.o: pilha.c
	@g++ -g pilha.c -c

arvoreBinaria.o: arvoreBinaria.c
	@g++ -g arvoreBinaria.c -c

clean:
	rm *.o prog
