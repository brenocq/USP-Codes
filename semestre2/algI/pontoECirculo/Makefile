all: build

run: build
	./prog

build: ponto.o circulo.o main.o
	gcc ponto.o circulo.o main.o -lm -o prog 

circulo.o:
	gcc -lm -c circulo.c

ponto.o:
	gcc -c ponto.c

main.o:
	gcc -c main.c

clean:
	rm *.o prog
