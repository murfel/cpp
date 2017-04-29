FLAGS = -std=c++11 -pedantic -Wall -Wextra -fsanitize=undefined -fdiagnostics-color=always -O0
# -ggdb3 -D_GLIBCXX_DEBUG

all: main
test_main: bin/test_main.o bin/huffman.o
	mkdir -p bin
	g++ -lgtest -lpthread bin/test_main.o bin/huffman.o -o test_main $(FLAGS)
bin/test_main.o: src/test_main.cpp bin/huffman.o
	mkdir -p bin
	g++ -c src/test_main.cpp -o bin/test_main.o $(FLAGS)


main: bin/main.o bin/huffman.o
	mkdir -p bin
	g++ bin/main.o bin/huffman.o -o main $(FLAGS)
bin/main.o: src/main.cpp bin/huffman.o
	mkdir -p bin
	g++ -c src/main.cpp -o bin/main.o $(FLAGS)
bin/huffman.o: src/huffman.cpp src/huffman.h
	mkdir -p bin
	g++ -c src/huffman.cpp -o bin/huffman.o $(FLAGS)
clean:
	rm -rf bin main
