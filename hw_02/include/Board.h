#pragma once

// capitalize these later
enum state { play, x_wins, o_wins, tie };
enum sign { none_sign = '.', x_sign = 'X', o_sign = 'O' };

class  Board {
public:
    Board(int size_ = 10, int win_len_ = 5);
    void move(int x, int y, sign cur_sign); //сделать ход
    bool canMove(int x, int y); //корректен ли ход
    state isWin(); // текущее состояние: играем дальше; ничья; 0 выиграли; X выиграли
    //Можно добавлять методы при необходимости.

    int size_;
    int win_len_;
    sign board_[10][10];
};
