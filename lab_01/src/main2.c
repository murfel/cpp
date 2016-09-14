#include "../include/function.h"

void logDebug(char c) {
}

int main() {
  int a = doComputation(5, 7.0);
  int b = 5;
  max(a, b);
  logDebug('!');
  return 0;
}
