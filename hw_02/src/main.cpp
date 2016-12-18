#include <cstdio>
#include <cstring>
#include <Board.h>
#include <BoardView.h>

int main(int argc, char ** argv) {
    bool silent = false;
    if (argc > 1) {
        if (strcmp(argv[1], "silent") == 0) {
            silent = true;
        }
    }

    Board b;
    View bv(b, !silent);

    bv.doGameCycle();

    return 0;
}
