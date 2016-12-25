# Copyright (C) Sayutin Dmitry, 2016.

# configuration
out         = main
out_test    = test
list_common = bin/Board.o bin/BoardView.o
list        = bin/main.o $(list_common) bin/NcursesBoardView.o
list_test   = bin/test_main.o bin/Test.o bin/BoardTest.o $(list_common)

flags         = -rdynamic -Wall -Wextra -ggdb3 -std=c++14
flags_compile = -Iinclude
flags_link    = -lncurses

# main targets

all:  $(out)
clean:
	@rm -rf bin main test_main

# work targets

main: bin $(list)
	g++ $(flags) $(list) -o $(out) $(flags_link)

test: bin $(list_test)
	g++ $(flags) $(list_test) -o test_main $(flags_link)

bin:
	mkdir -p bin

bin/test_main.o: test/test_main.cpp
	g++ $(flags) $(flags_compile) -c test/test_main.cpp -o bin/test_main.o

bin/Test.o: test/Test.cpp include/Test.h
	g++ $(flags) $(flags_compile) -c test/Test.cpp -o bin/Test.o

bin/BoardTest.o: test/BoardTest.cpp include/BoardTest.h
	g++ $(flags) $(flags_compile) -c test/BoardTest.cpp -o bin/BoardTest.o

bin/%.o: src/%.cpp include
	g++ $(flags) $(flags_compile) -c $< -o $@


