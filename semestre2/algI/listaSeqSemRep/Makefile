all: build

run: build
	./prog

build: lista.o main.o
	gcc lista.o main.o -o prog

clean:
	rm *.o prog
