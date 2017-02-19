#include "employees.h"
#include <stdint.h>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    EmployeesArray employee_list;
    string s;
    int32_t type;

    while(1) {
        cin >> s;
        if (s == "load") {
            cin >> s;
            ifstream f;
            f.open(s.c_str(), ios_base::binary);
            f >> employee_list;
            f.close();
        }
        else if (s == "list") {
            cout << employee_list;
        }
        else if (s == "add") {
            cin >> type;
            if (type == DEVELOPER) {
                Developer * worker = new Developer();
                cin >> *worker;
                employee_list.add(worker);
            }
            else if (type == SALES_MANAGER) {
                SalesManager * worker = new SalesManager();
                cin >> *worker;
                employee_list.add(worker);
            }
            else {
                cout << "The type " << type << " is not recognized.";
            }
        }
        else if (s == "save") {
            cin >> s;
            ofstream f;
            f.open(s.c_str(), ios_base::binary);
            f << employee_list;
            f.close();
        }
        else if (s == "exit") {
            break;
        }
        else {
            cout << "The keyword " << s << " is not recognized.";
        }
    }

    return 0;
}
