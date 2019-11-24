all: build

run: build
	./prog

build: lista.o hashMonk.o
	gcc lista.o hashMonk.o -o prog

clean:
	rm *.o prog
