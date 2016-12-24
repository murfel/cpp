#pragma once

#include <Board.h>

class NcursesView {
public:
    NcursesView(Board &m);
    ~NcursesView();
    void showBoard();
    void doGameCycle();
private:
    Board &model_;
};
