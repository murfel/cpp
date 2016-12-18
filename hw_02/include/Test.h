#pragma once

#include <cstddef>

class Test {
protected:
    static int failedNum; // количество тестов, которые сломались
    static int totalNum;  // общее количество тестов
public:
    /*
    Если условие expr не выполнено, то функция check выводит информацию об ошибке; эта информация должна содержать имя функции с тестом, имя файла с тестом и номер строки, на которой находиться вызов check (например, “test failed: testIsWIn() in TestBoard.cpp:34”).
    */
    static void check(bool expr, const char *func, const char  *filename, size_t lineNum);

    /*
    Функция выводит финальную статистику тестирования, например, “All test passed.” или “Failed 2 of 8 tests.”.
    */
    static void showFinalResult();

    /*
    Эта функция запускает все тесты из производного класса. Именно эта функция запускается из main в test.cpp.
    */
    virtual void runAllTests() = 0;


    // Можно добавлять методы при необходимости
};
