#include <cstdio>
#include <cstdlib>
#include <BoardView.h>

View::View(Board &m, bool show_board_) : model_(m), show_board_(show_board_) {
}

void View::showBoard() {
    for (int i = 0; i < model_.size_; i++) {
        for (int j = 0; j < model_.size_; j++) {
            fprintf(stdout, "%c", model_.board_[j][i]);
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}

void View::doGameCycle() {
    int x, y;
    sign cur_symbol = o_sign;
    bool bad_move;

    while (model_.isWin() == play) {
        bad_move = false;

        do {
            if (bad_move) {
                if (x == -1 && y == -1) {
                    fprintf(stdout, "Bye!\n");
                    exit(1);
                }
                fprintf(stdout, "Bad move!\n");
            }
            fprintf(stdout, "%c move: ", cur_symbol);
            fscanf(stdin, "%d %d", &y, &x); // note the reverse order
            bad_move = true;
        }
        while (!model_.canMove(x, y));

        model_.move(x, y, cur_symbol);
        cur_symbol = cur_symbol == o_sign ? x_sign : o_sign;

        if (show_board_) {
            showBoard();
        }
    }

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
