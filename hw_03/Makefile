FLAGS = -std=c++11 -pedantic -Wall -Wextra -fsanitize=undefined -fdiagnostics-color=always -O0
# -ggdb3 -D_GLIBCXX_DEBUG

all: huffman
main_test: bin/test.o bin/huffman.o
	mkdir -p bin
	g++ -lgtest -lpthread bin/test.o bin/huffman.o -o main_test $(FLAGS)
bin/test.o: test/test.cpp bin/huffman.o
	mkdir -p bin
	g++ -c test/test.cpp -o bin/test.o $(FLAGS) -Isrc
huffman: bin/main.o bin/huffman.o
	mkdir -p bin
	g++ bin/main.o bin/huffman.o -o huffman $(FLAGS)
bin/main.o: src/main.cpp bin/huffman.o
	mkdir -p bin
	g++ -c src/main.cpp -o bin/main.o $(FLAGS)
bin/huffman.o: src/huffman.cpp src/huffman.h
	mkdir -p bin
	g++ -c src/huffman.cpp -o bin/huffman.o $(FLAGS)
clean:
	rm -rf bin main main_test
