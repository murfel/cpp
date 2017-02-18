#include "employees.h"

#include <stdint.h>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

ostream& operator<<(ostream& os, Employee& o) {
  o.print(os);
  return os;
}

ofstream& operator<<(ofstream& ofs, Employee& o) {
  o.print(ofs);
  return ofs;
}

EmployeesArray::EmployeesArray() : _size(0), _capacity(4) {
    _employees = new Employee * [_capacity];
}

void EmployeesArray::add (const Employee *e) {
    if (_size == _capacity) {
        _capacity *= 2;
        Employee ** temp = new Employee * [_capacity];
        for (int i = 0; i < _size; i++) {
            temp[i] = _employees[i];
        }
        delete[] _employees;
        _employees = temp;
    }
    _employees[_size++] = (Employee *) e;
}

int EmployeesArray::total_salary() const {
    int total = 0;
    for (int i = 0; i < _size; i++) {
        total += _employees[i]->salary();
    }
    return total;
}


ostream& Developer::print(ostream& os) {
    os << "Developer";
    os << "\nName: " << _name;
    os << "\nBase Salary: " << _base_salary;
    os << "\nHas bonus: " << (_has_bonus? "+" : "-");
    os << "\n";
    return os;
}

ofstream& Developer::print(ofstream& ofs) {
    ofs.write((const char *)&type, sizeof(type));
    ofs.write((const char *)_name, sizeof(strlen(_name)) + 1);
    ofs.write((const char *)&_base_salary, sizeof(_base_salary));
    ofs.write((const char *)&_has_bonus, sizeof(_has_bonus));
    return ofs;
}


ostream& SalesManager::print(ostream& os) {
    os << "Sales Manager";
    os << "\nName: " << _name;
    os << "\nBase Salary: " << _base_salary;
    os << "\nSold items: " << _sold_nm;
    os << "\nItem price: " << _price;
    os << "\n";
    return os;
}

ofstream& SalesManager::print(ofstream& ofs) {
    ofs.write((const char *)&type, sizeof(type));
    ofs.write((const char *)_name, sizeof(strlen(_name)) + 1);
    ofs.write((const char *)&_base_salary, sizeof(_base_salary));
    ofs.write((const char *)&_sold_nm, sizeof(_sold_nm));
    ofs.write((const char *)&_price, sizeof(_price));
    return ofs;
}



istream& operator>>(istream& is, Developer& o) {
    string s;
    is >> s >> o._base_salary >> o._has_bonus;
    o._name = new char [s.length() + 1];
    strcpy(o._name, s.c_str());
    return is;
}


ifstream& operator>>(ifstream & ifs, Developer& o) {
    string s;
    char c = 1;
    while (c != 0) {
        ifs.read(&c, 1);
        s += c;
    }
    o._name = new char [s.length() + 1];
    strcpy(o._name, s.c_str());
    ifs.read((char *)&o._base_salary, sizeof(o._base_salary));
    ifs.read((char *)&o._has_bonus, sizeof(o._has_bonus));
    return ifs;
}


istream& operator>>(istream& is, SalesManager& o) {
    string s;
    is >> s >> o._base_salary >> o._sold_nm >> o._price;
    o._name = new char [s.length() + 1];
    strcpy(o._name, s.c_str());
    return is;
}


ifstream& operator>>(ifstream& ifs, SalesManager& o) {
    string s;
    char c = 1;
    while (c != 0) {
        ifs.read(&c, 1);
        s += c;
    }
    o._name = new char [s.length() + 1];
    strcpy(o._name, s.c_str());
    ifs.read((char *)&o._base_salary, sizeof(o._base_salary));
    ifs.read((char *)&o._sold_nm, sizeof(o._sold_nm));
    ifs.read((char *)&o._price, sizeof(o._price));
    return ifs;
}


// текстовый вывод в консоль всего списка
ostream& operator<<(ostream& os, EmployeesArray& o) {
    for (int i = 0; i < o._size; i++) {
        os << i + 1 << ". ";
        o._employees[i]->print(os);
    }
    os << "== Total salary: " << o.total_salary() << "\n";
    return os;
}

// бинарный вывод в файл всего списка
ofstream& operator<<(ofstream& ofs, EmployeesArray& o) {
    ofs.write((const char *)&o._size, sizeof(int32_t));
    for (int i = 0; i < o._size; i++) {
        o._employees[i]->print(ofs);
    }
    return ofs;
}

// бинарный ввод из файла
ifstream& operator>>(ifstream& ifs, EmployeesArray& o) {
    int32_t count;
    ifs.read((char *)&count, sizeof(count));
    int32_t type;
    while(count--) {
        ifs.read((char *)&type, sizeof(type));
        if (type == DEVELOPER) {
            Developer * worker = new Developer();
            ifs >> *worker;
            o.add(worker);
        }
        else if (type == SALES_MANAGER) {
            SalesManager * worker = new SalesManager();
            ifs >> *worker;
            o.add(worker);
        }
    }
    return ifs;
}
