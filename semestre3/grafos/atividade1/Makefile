all: build

run: build
	./prog

build: grafo.o main.o
	gcc grafo.o main.o -lm -o prog 

grafo.o:
	gcc -c grafo.c

main.o:
	gcc -c main.c

clean:
	rm -rf *.o prog
