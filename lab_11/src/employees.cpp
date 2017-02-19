#include "employees.h"

#include <stdint.h>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

ostream& operator<<(ostream& os, const Employee& o) {
    o.print(os);
    return os;
}

ofstream& operator<<(ofstream& ofs, const Employee& o) {
    o.print(ofs);
    return ofs;
}

istream& operator>>(istream& is, Employee& o) {
    o.read(is);
    return is;
}

ifstream& operator>>(ifstream& ifs, Employee& o) {
    o.read(ifs);
    return ifs;
}

EmployeesArray::EmployeesArray() : _size(0), _capacity(4) {
    _employees = new Employee * [_capacity];
}

EmployeesArray::~EmployeesArray() {
    for (int i = 0; i < _size; i++) {
        delete _employees[i];
    }
    delete[] _employees;
}

void EmployeesArray::add(const Employee *e) {
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

Employee::~Employee() {
    delete[] _name;
}

Developer::Developer() {
    type = DEVELOPER;
    _name = new char [1];
}

ostream& Developer::print(ostream& os) const {
    os << "Developer";
    os << "\nName: " << _name;
    os << "\nBase Salary: " << _base_salary;
    os << "\nHas bonus: " << (_has_bonus? "+" : "-");
    os << "\n";
    return os;
}

ofstream& Developer::print(ofstream& ofs) const {
    ofs.write((const char *)&type, sizeof(type));
    ofs.write((const char *)_name, strlen(_name) + 1);
    ofs.write((const char *)&_base_salary, sizeof(_base_salary));
    ofs.write((const char *)&_has_bonus, sizeof(_has_bonus));
    return ofs;
}

istream& Developer::read(istream& is) {
    is >> *this;
    return is;
}

ifstream& Developer::read(ifstream& ifs) {
    ifs >> *this;
    return ifs;
}

SalesManager::SalesManager() {
    type = SALES_MANAGER;
    _name = new char [1];
}

ostream& SalesManager::print(ostream& os) const {
    os << "Sales Manager";
    os << "\nName: " << _name;
    os << "\nBase Salary: " << _base_salary;
    os << "\nSold items: " << _sold_nm;
    os << "\nItem price: " << _price;
    os << "\n";
    return os;
}

ofstream& SalesManager::print(ofstream& ofs) const {
    ofs.write((const char *)&type, sizeof(type));
    ofs.write((const char *)_name, strlen(_name) + 1);
    ofs.write((const char *)&_base_salary, sizeof(_base_salary));
    ofs.write((const char *)&_sold_nm, sizeof(_sold_nm));
    ofs.write((const char *)&_price, sizeof(_price));
    return ofs;
}

istream& SalesManager::read(istream& is) {
    is >> *this;
    return is;
}

ifstream& SalesManager::read(ifstream& ifs) {
    ifs >> *this;
    return ifs;
}

istream& operator>>(istream& is, Developer& o) {
    string s;
    is >> s >> o._base_salary >> o._has_bonus;
    delete[] o._name;
    o._name = new char [s.length() + 1];
    strcpy(o._name, s.c_str());
    return is;
}

char * read_name(ifstream& ifs) {
    string s;
    char c = 1;
    while (c != 0) {
        ifs.read(&c, 1);
        s += c;
    }
    char *name = new char [s.length() + 1];
    strcpy(name, s.c_str());
    return name;
}

ifstream& operator>>(ifstream& ifs, Developer& o) {
    delete[] o._name;
    o._name = read_name(ifs);
    ifs.read((char *)&o._base_salary, sizeof(o._base_salary));
    ifs.read((char *)&o._has_bonus, sizeof(o._has_bonus));
    return ifs;
}

istream& operator>>(istream& is, SalesManager& o) {
    string s;
    is >> s >> o._base_salary >> o._sold_nm >> o._price;
    delete[] o._name;
    o._name = new char [s.length() + 1];
    strcpy(o._name, s.c_str());
    return is;
}

ifstream& operator>>(ifstream& ifs, SalesManager& o) {
    delete[] o._name;
    o._name = read_name(ifs);
    ifs.read((char *)&o._base_salary, sizeof(o._base_salary));
    ifs.read((char *)&o._sold_nm, sizeof(o._sold_nm));
    ifs.read((char *)&o._price, sizeof(o._price));
    return ifs;
}

// текстовый вывод в консоль всего списка
ostream& operator<<(ostream& os, const EmployeesArray& o) {
    for (int i = 0; i < o._size; i++) {
        os << i + 1 << ". ";
        o._employees[i]->print(os);
    }
    os << "== Total salary: " << o.total_salary() << "\n";
    return os;
}

// бинарный вывод в файл всего списка
ofstream& operator<<(ofstream& ofs, const EmployeesArray& o) {
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
