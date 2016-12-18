#pragma once

#define DO_CHECK(EXPR) BoardTest::check(EXPR, __FUNCTION__, __FILE__, __LINE__);

#include <Test.h>

class BoardTest: public Test {
public:
    void testCanMovePositive();
    void testCanMoveNegative();
    void testCanMoveMirror();

    void testMoveX();
    void testMoveO();
    void testMoveOX();

    void testIsWinPlay();
    void testIsWinVerticalX();
    void testIsWinHorizontalO();
    void testIsWinSlashX();
    void testIsWinSlashX2();
    void testIsWinSlashX3();
    void testIsWinBackslashO();
    void testIsWinBackslashO2();
    void testIsWinBackslashO3();
    void testIsWinTie();

    void runAllTests();
};
