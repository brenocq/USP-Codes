all: build

run: build
	./prog

build: carro.o fila.o pilha.o estacionamento.o main.o

main.o: main.c
	@g++ -g main.c -Wall -o prog carro.o fila.o pilha.o estacionamento.o

carro.o: carro.c
	@g++ -g carro.c -c

fila.o: fila.c
	@g++ -g fila.c -c

pilha.o: pilha.c
	@g++ -g pilha.c -c

estacionamento.o: estacionamento.c
	@g++ -g estacionamento.c -c

clean:
	rm *.o prog
