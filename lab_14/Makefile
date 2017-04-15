FLAGS	= -Iinclude -std=c++11 -pedantic -Wall -Wextra -fdiagnostics-color=always

all: main
main: bin/main.o bin/matrix.o
	mkdir -p bin
	g++ -g bin/main.o bin/matrix.o -o main $(FLAGS)
bin/matrix.o: src/matrix.cpp include/matrix.h
	mkdir -p bin
	g++ -g -c src/matrix.cpp -o bin/matrix.o $(FLAGS)
bin/main.o: src/main.cpp bin/matrix.o
	mkdir -p bin
	g++ -g -c src/main.cpp -o bin/main.o $(FLAGS)
clean:
	rm -rf bin main
