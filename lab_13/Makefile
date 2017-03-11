flags	= -Iinclude -std=c++03 -pedantic -Wall -Wextra

all: main
main: bin/main.o
	mkdir -p bin
	g++ -g  bin/main.o -o main $(flags)
bin/main.o: src/main.cpp include/my_array.h
	mkdir -p bin
	g++ -g -c src/main.cpp -o bin/main.o $(flags)
clean:
	rm -rf bin main
