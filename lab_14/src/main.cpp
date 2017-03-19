#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>

#include "matrix.h"

using namespace std;

int main(int, char **) {
  std::string cmd, reg1, reg2, fname;
  map<string, Matrix*> regs;
  int rows, cols, val, row_index, col_index;
  fstream file;

  for (int i = 0; i < 10; ++i) {
    regs["$" + to_string(i)] = new Matrix(0, 0);
  }

  while (1) {
    cin >> cmd;

    try {
      if (cmd == "exit") {
        break;
      } else if (cmd == "print") {
        cin >> reg1;
        for (size_t i = 0; i < regs[reg1]->get_rows(); ++i) {
          for (size_t j = 0; j < regs[reg1]->get_cols(); ++j) {
            cout << regs[reg1]->get(i, j) << " ";
          }
          cout << endl;
        }
      } else if (cmd == "load") {

        cin >> reg1 >> fname;
        delete regs[reg1];

        file.open(fname, fstream::in);
        file >> rows >> cols;
        regs[reg1] = new Matrix(rows, cols);
        for (int i = 0; i < rows; ++i) {
          for (int j = 0; j < cols; ++j) {
              file >> val;
              regs[reg1]->set(i, j, val);
          }
        }
        file.close();
      } else if (cmd == "add") {
        cin >> reg1 >> reg2;
        *regs[reg1] += *regs[reg2];
      } else if (cmd == "mul") {
        cin >> reg1 >> reg2;
        *regs[reg1] *= *regs[reg2];
      } else if (cmd == "elem") {
        cin >> reg1 >> row_index >> col_index;
        cout << regs[reg1]->get(row_index, col_index);
      }
    }
    catch (MatrixException& e) {
      cout << e.what() << endl;
    }
  }

  for (map<string, Matrix*>::iterator it = regs.begin(); it != regs.end(); ++it) {
    delete it->second;
  }


  return 0;
}
