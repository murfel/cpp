#include <Test.h>
#include <BoardTest.h>
#include <Board.h>

#include <iostream>
#include <string>

using namespace std;

void BoardTest::testCanMovePositive() {
    Board b;
    bool can_move = true;
    for (int i = 0; i < b.size_; i++) {
        for (int j = 0; j< b.size_; j++) {
            if (!b.canMove(i, j)) {
                can_move = false;
                break;
            }
        }
    }
    DO_CHECK(can_move);
}

void BoardTest::testCanMoveNegative() {
    Board b;
    b.move(0, 0, x_sign);
    DO_CHECK(b.canMove(0, 0) == false);
}

void BoardTest::testCanMoveMirror() {
    Board b;
    b.move(0, 1, o_sign);
    DO_CHECK(b.canMove(1, 0) == true);
}

void BoardTest::testMoveX() {
    Board b;
    b.move(1, 0, x_sign);
    DO_CHECK(b.board_[1][0] == x_sign);
}

void BoardTest::testMoveO() {
    Board b;
    b.move(1, 0, o_sign);
    DO_CHECK(b.board_[1][0] == o_sign);
}

void BoardTest::testMoveOX() {
    Board b;
    bool moves_made;
    b.move(1, 0, o_sign);
    b.move(0, 1, x_sign);
    moves_made = b.board_[1][0] == o_sign ? true : false;
    moves_made = b.board_[0][1] == x_sign ? true : false;
    DO_CHECK(moves_made);
}

void BoardTest::testIsWinPlay() {
    Board b;
    DO_CHECK(b.isWin() == play);
}

void BoardTest::testIsWinVerticalX() {
    Board b;
    b.move(0, 0, x_sign);
    b.move(4, 5, o_sign);
    b.move(0, 1, x_sign);
    b.move(3, 5, o_sign);
    b.move(0, 2, x_sign);
    b.move(5, 5, o_sign);
    b.move(0, 3, x_sign);
    b.move(3, 3, o_sign);
    b.move(0, 4, x_sign);
    DO_CHECK(b.isWin() == x_wins);
}

void BoardTest::testIsWinHorizontalO() {
    Board b;
    b.move(2, 3, o_sign);
    b.move(3, 3, o_sign);
    b.move(4, 3, o_sign);
    b.move(5, 3, o_sign);
    b.move(6, 3, o_sign);
    DO_CHECK(b.isWin() == o_wins);
}

void BoardTest::testIsWinSlashX() {
    // the topmost diagonal
    Board b(4, 3);
    b.move(0, 2, x_sign);
    b.move(1, 1, x_sign);
    b.move(2, 0, x_sign);
    DO_CHECK(b.isWin() == x_wins);
}

void BoardTest::testIsWinSlashX2() {
    // the main diagonal
    Board b(4, 3);
    b.move(1, 2, x_sign);
    b.move(2, 1, x_sign);
    b.move(3, 0, x_sign);
    DO_CHECK(b.isWin() == x_wins);
}

void BoardTest::testIsWinSlashX3() {
    // the bottom diagonal
    Board b(4, 3);
    b.move(1, 3, x_sign);
    b.move(2, 2, x_sign);
    b.move(3, 1, x_sign);
    DO_CHECK(b.isWin() == x_wins);
}

void BoardTest::testIsWinBackslashO() {
    // the bottom diagonal
    Board b(4, 3);
    b.move(0, 1, o_sign);
    b.move(1, 2, o_sign);
    b.move(2, 3, o_sign);
    DO_CHECK(b.isWin() == o_wins);
}

void BoardTest::testIsWinBackslashO2() {
    // the main diagonal
    Board b(4, 3);
    b.move(0, 0, o_sign);
    b.move(1, 1, o_sign);
    b.move(2, 2, o_sign);
    DO_CHECK(b.isWin() == o_wins);
}

void BoardTest::testIsWinBackslashO3() {
    // the topmost diagonal
    Board b(4, 3);
    b.move(1, 0, o_sign);
    b.move(2, 1, o_sign);
    b.move(3, 2, o_sign);
    DO_CHECK(b.isWin() == o_wins);
}

void BoardTest::testIsWinTie() {
    Board b(3, 3);
    b.move(0, 0, o_sign);
    b.move(0, 1, o_sign);
    b.move(0, 2, x_sign);
    b.move(1, 0, x_sign);
    b.move(1, 1, x_sign);
    b.move(1, 2, o_sign);
    b.move(2, 0, o_sign);
    b.move(2, 1, o_sign);
    b.move(2, 2, x_sign);
    DO_CHECK(b.isWin() == tie);
}

void BoardTest::runAllTests() {
    testCanMovePositive();
    testCanMoveNegative();
    testCanMoveMirror();

    testMoveX();
    testMoveO();
    testMoveOX();

    testIsWinPlay();
    testIsWinVerticalX();
    testIsWinHorizontalO();
    testIsWinSlashX();
    testIsWinSlashX2();
    testIsWinSlashX3();
    testIsWinBackslashO();
    testIsWinBackslashO2();
    testIsWinBackslashO3();
    testIsWinTie();
}
