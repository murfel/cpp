#include <cstdio>
#include <cstring>
#include <Board.h>
#include <BoardView.h>
#include <NcursesBoardView.h>

int main(int argc, char ** argv) {
    bool silent = false;
    bool curses = false;
    if (argc > 1) {
        if (strcmp(argv[1], "silent") == 0) {
            silent = true;
        }
        if (strcmp(argv[1], "curses") == 0) {
            curses = true;
        }
    }

    Board b;
    if (curses) {
        NcursesView nbv(b);
        nbv.doGameCycle();
    }
    else {
        View bv(b, !silent);
        bv.doGameCycle();
    }
    return 0;
}
