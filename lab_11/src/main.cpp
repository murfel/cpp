#include "employees.h"
#include <stdint.h>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    EmployeesArray * employee_list = new EmployeesArray();
    string s;
    int32_t type;

    while(1) {
        cin >> s;
        if (s.compare("load") == 0) {
            cin >> s;
            ifstream f;
            f.open(s, ios_base::binary);
            f >> *employee_list;
            f.close();
        }
        else if (s.compare("list") == 0) {
            cout << *employee_list;
        }
        else if (s.compare("add") == 0) {
            cin >> type;
            if (type == DEVELOPER) {
                Developer * worker = new Developer();
                cin >> *worker;
                employee_list->add(worker);
            }
            else if (type == SALES_MANAGER) {
                SalesManager * worker = new SalesManager();
                cin >> *worker;
                employee_list->add(worker);
            }
            else {
                cout << "The type " << type << " is not recognized.";
            }
        }
        else if (s.compare("save") == 0) {
            cin >> s;
            ofstream f;
            f.open(s, ios_base::binary);
            f << *employee_list;
            f.close();
        }
        else if (s.compare("exit") == 0) {
            break;
        }
        else {
            cout << "The keyword " << s << " is not recognized.";
        }
    }

    return 0;
}
