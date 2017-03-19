#include <string>
#include <map>
#include <iostream>
#include <cstdio>
#include <cassert>

#include "matrix.h"

using namespace std;

int main(int, char **) {
  std::string cmd, arg1, arg2, arg3, reg;
  map<string, Matrix*> regs;
  int rows, cols, val, pos_i, pos_j;

  for (int i = 0; i < 10; ++i) {
    regs["$" + to_string(i)] = new Matrix(0, 0);
  }

/*
  // This works just fine.
  while (1) {
    cin >> cmd;
    if (cmd == "exit") {
      cout << "exiting!" << endl;
      exit(0);
    } else if (cmd == "foo") {
      cout << "foobar!" << endl;
    }
  }
*/

  while (1) {
    cin >> cmd;
    if (cmd == "exit") {
      break;
    } else if (cmd == "print") {
      cin >> arg1;
      for (size_t i = 0; i < regs[arg1]->get_rows(); ++i) {
        for (size_t j = 0; j < regs[arg1]->get_cols(); ++j) {
          cout << regs[arg1]->get(i, j) << " ";
        }
        cout << endl;
      }
    } else if (cmd == "load") {

      cin >> arg1 >> arg2;
      delete regs[arg1];

      freopen(arg2.c_str(), "r", stdin);
      cin >> rows >> cols;
      cerr << rows << " " << cols << endl;

      regs[arg1] = new Matrix(rows, cols);
      /*
      for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> val;
            regs[arg1]->set(i, j, val);
        }
      }
      */
      fclose(stdin);
      cout << "loaded\n";
    } else if (cmd == "add") {
      cin >> arg1 >> arg2;
      try {
        *regs[arg1] += *regs[arg2];
      }
      catch (MatrixException& e) {
        cout << e.what();
      }
    } else if (cmd == "mul") {
      cin >> arg1 >> arg2;
      try {
        *regs[arg1] *= *regs[arg2];
      }
      catch (MatrixException& e) {
        cout << e.what() << endl;
      }
    } else if (cmd == "elem") {
      cin >> arg1 >> pos_i >> pos_j;
      try {
        cout << regs[arg1]->get(pos_i, pos_j);
      }
      catch (MatrixException& e) {
        cout << e.what() << endl;
      }
    }
  }

  for (map<string, Matrix*>::iterator it = regs.begin(); it != regs.end(); ++it) {
    delete it->second;
  }

  return 0;
}
