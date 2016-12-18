#include <Test.h>
#include <cstdio>

int Test::failedNum = 0;
int Test::totalNum = 0;

void Test::check(bool expr, const char *func, const char  *filename, size_t lineNum) {
    totalNum++;
    if (!expr) {
        failedNum++;
        fprintf(stdout, "test failed: %s in %s:%lud\n", func, filename, lineNum);
    }
}

void Test::showFinalResult() {
    if (!failedNum) {
        fprintf(stdout, "OK\n");
    }
    else {
        fprintf(stdout, "Failed %d of %d tests.\n", failedNum, totalNum);
    }
}
