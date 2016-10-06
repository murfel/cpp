all: ms_cli
ms_cli: bin/main.o
	mkdir -p bin
	gcc bin/main.o -o ms_cli
bin/main.o: src/main.c bin/mergesort.o
	mkdir -p bin
	gcc -c src/main.c -o bin/main.o
bin/mergesort.o: src/mergesort.c include/mergesort.h
	mkdir -p bin
	gcc -c src/mergesort.c -o bin/mergesort.o
clean:
	rm -r bin
