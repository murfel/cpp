all: lab2
lab2: bin/test_str.o
	mkdir -p bin
	gcc bin/test_str.o -o lab2
bin/str.o: src/str.c include/str.h
	mkdir -p bin	
	gcc -c src/str.c -o bin/str.o
bin/test_str.o: bin/str.o src/test_str.c include/test_str.h
	mkdir -p bin
	gcc -c src/test_str.c -o bin/test_str.o
clean:
	rm -r bin
