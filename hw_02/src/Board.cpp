#include <Board.h>

#include <iostream>
#include <string>

using namespace std;

Board::Board(int size_ /* = 10 */, int win_len_ /* = 5 */) : size_(size_), win_len_(win_len_) {
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            board_[i][j] = none_sign;
        }
    }

}

void Board::move(int x, int y, sign cur_sign) {
    if (canMove(x, y)) {
        board_[x][y] = cur_sign;
    }
}

bool Board::canMove(int x, int y) {
    if (x < 0 || x >= size_ || y < 0 || y >= size_) {
        return false;
    }
    if (board_[x][y] == none_sign) {
        return true;
    }
    return false;
}

state Board::isWin() {
    int count;
    sign cur_symbol;

    // check for a vertical win
    for (int i = 0; i < size_; i++) {
        count = 1;
        cur_symbol = none_sign;
        for (int j = 0; j < size_; j++) {
            if (cur_symbol == none_sign) {
                cur_symbol = board_[i][j];
                continue;
            }
            if (board_[i][j] == cur_symbol) {
                count++;
                if (count == win_len_) {
                    return cur_symbol == x_sign ? x_wins : o_wins;
                }
            }
            else {
                count = 1;
                cur_symbol = board_[i][j];
            }
        }
    }

    // check for a horizontal win
    for (int j = 0; j < size_; j++) {
        count = 1;
        cur_symbol = none_sign;
        for (int i = 0; i < size_; i++) {
            if (cur_symbol == none_sign) {
                cur_symbol = board_[i][j];
                continue;
            }
            if (board_[i][j] == cur_symbol) {
                count++;
                if (count == win_len_) {
                    return cur_symbol == x_sign ? x_wins : o_wins;
                }
            }
            else {
                count = 1;
                cur_symbol = board_[i][j];
            }
        }
    }

    // check for a forward slash win
    int j;
    for (int d = win_len_ - 1; d <= 2 * size_ - win_len_ - 1; d++) {
        count = 1;
        cur_symbol = none_sign;
        for (int i = 0; i <= d; i++) {
            j = d - i;
            if (cur_symbol == none_sign) {
                cur_symbol = board_[i][j];
                continue;
            }
            if (board_[i][j] == cur_symbol) {
                count++;
                if (count == win_len_) {
                    return cur_symbol == x_sign ? x_wins : o_wins;
                }
            }
            else {
                count = 1;
                cur_symbol = board_[i][j];
            }
        }
    }

    int new_i, new_j;
    for (int d = win_len_ - 1; d <= 2 * size_ - win_len_ - 1; d++) {
        count = 1;
        cur_symbol = none_sign;
        for (int i = 0; i <= d; i++) {
            j = d - i;
            // rotate the coordinates counterclockwise
            new_i = j;
            new_j = size_ - i - 1;

            if (cur_symbol == none_sign) {
                cur_symbol = board_[new_i][new_j];
                continue;
            }
            if (board_[new_i][new_j] == cur_symbol) {
                count++;
                if (count == win_len_) {
                    return cur_symbol == x_sign ? x_wins : o_wins;
                }
            }
            else {
                count = 1;
                cur_symbol = board_[new_i][new_j];
            }
        }
    }

    bool is_tie = true;
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            if (board_[i][j] == none_sign) {
                is_tie = false;
            }
        }
    }

    return is_tie ? tie : play;
}
