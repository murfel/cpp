all: pose_db
pose_db: bin/main.o
	mkdir -p bin
	gcc bin/main.o -o pose_db
bin/main.o: src/main.c bin/clist.o
	mkdir -p bin
	gcc -c src/main.c -o bin/main.o
bin/clist.o: src/clist.c include/clist.h
	mkdir -p bin
	gcc -c src/clist.c -o bin/clist.o
clean:
	rm -r bin
