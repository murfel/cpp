#pragma once

#include <Board.h>

class View {
public:
    View(Board &m, bool show_board_ = true);
    void showBoard(); //вывод доски на экран
    void doGameCycle(); //основной цикл игры: ввод хода, вывод на экран доски, проверка текущего состояния
private:
    Board &model_;
    bool show_board_ = true;
};
