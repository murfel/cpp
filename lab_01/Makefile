all: lab1
lab1: bin/main.o bin/algorithm.o bin/io.o bin/util.o
	gcc bin/main.o bin/algorithm.o bin/io.o bin/util.o -o lab1
bin/main.o: src/main.c bin/function.o
	gcc -c src/main.c -o bin/main.o
bin/algorithm.o: src/algorithm.c bin/function.o
	gcc -c src/algorithm.c -o bin/algorithm.o
bin/io.o: src/io.c
	gcc -c src/io.c -o bin/io.o
bin/util.o: src/util.c bin/function.o
	gcc -c src/util.c -o bin/util.o
bin/function.o: include/function.h
	gcc -c include/function.h -o bin/function.o
clean:
	rm -f bin/*.o
