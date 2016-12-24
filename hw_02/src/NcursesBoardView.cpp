#include <NcursesBoardView.h>
#include <cstdio>
#include <cstdlib>
#include <ncurses.h>

NcursesView::NcursesView(Board &m) : model_(m) {
    initscr();
    clear();
    noecho();
    cbreak();
    raw();
    keypad(curscr, TRUE);
}

NcursesView::~NcursesView() {
    clear();
    endwin();

    state status = model_.isWin();

    if (status == x_wins) {
        fprintf(stdout, "X wins!\n");
    }
    else if (status == o_wins) {
        fprintf(stdout, "O wins!\n");
    }
    else {
        fprintf(stdout, "Draw.\n");
    }
}

void NcursesView::showBoard() {
    for (int i = 0; i < model_.size_; i++) {
        for (int j = 0; j < model_.size_; j++) {
            fprintf(stdout, "%c", model_.board_[j][i]);
            mvaddch(j, i, model_.board_[j][i]);
        }
    }
}

void NcursesView::doGameCycle() {
    int x = 0;
    int y = 0;
    int c;
    sign cur_symbol = o_sign;

    showBoard();
    move(y, x);

    while (model_.isWin() == play) {
        do {
            c = ' ' + 1;
            while (c != ' ') {
                c = getch();
                if (c == 'w') {
                    if (y - 1 >= 0) {
                        move(--y, x);
                    }
                }
                else if (c == 's') {
                    if (y + 1 < model_.size_) {
                        move(++y, x);
                    }
                }
                else if (c == 'd') {
                    if (x + 1 < model_.size_) {
                        move(y, ++x);
                    }
                }
                else if (c == 'a') {
                    if (x - 1 >= 0) {
                        move(y, --x);
                    }
                }
                else if (c == 'x') {
                    return;
                }
            }
        }
        while (!model_.canMove(y, x));

        model_.move(y, x, cur_symbol);
        cur_symbol = cur_symbol == o_sign ? x_sign : o_sign;

        showBoard();
        move(y, x);
    }
    printf("\n");
    clear();
    endwin();
}
