#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <iostream>

using namespace std;

enum employees {DEVELOPER = 1, SALES_MANAGER};

class Employee {
public:
    ~Employee();
    virtual int salary() const = 0;
    virtual ostream& print(ostream& os) = 0;
    virtual ofstream& print(ofstream& os) = 0;
    friend ostream& operator<<(ostream& os, Employee& o);
    friend ofstream& operator<<(ofstream& ofs, Employee& o);
protected:
    int32_t type;
    char *_name;
    int32_t _base_salary;
};


class Developer : public Employee {
public:
    //virtual ~Developer();
    int salary() const {
        int salary = _base_salary;
        if (_has_bonus) { salary += 1000; }
        return salary;
    }
    ostream& print(ostream& os);
    ofstream& print(ofstream& ofs);
    friend istream& operator>>(istream& is, Developer& o);
    friend ifstream& operator>>(ifstream& ifs, Developer& o);
private:
    int32_t type = DEVELOPER;
    bool _has_bonus;
};


class SalesManager : public Employee {
public:
    //virtual ~SalesManager();
    int salary() const {
        return _base_salary + _sold_nm * _price * 0.01;
    }
    ostream& print(ostream& os);
    ofstream& print(ofstream& ofs);
    friend istream& operator>>(istream& is, SalesManager& e);
    friend ifstream& operator>>(ifstream& ifs, SalesManager& e);
private:
    int32_t type = SALES_MANAGER;
    int32_t _sold_nm, _price;
};


class EmployeesArray {
public:
    EmployeesArray();
    ~EmployeesArray();
    void add(const Employee *e);
    int total_salary() const;
    friend ostream& operator<<(ostream& os, EmployeesArray& o);
    friend ofstream& operator<<(ofstream& ofs, EmployeesArray& o);
    friend ifstream& operator>>(ifstream& ifs, EmployeesArray& o);
private:
    Employee **_employees;
    int32_t _size = 0;
    int32_t _capacity = 0;
};


ostream& operator<<(ostream& os, Employee& o);
ofstream& operator<<(ofstream& ofs, Employee& o);

char * read_name(ifstream& ifs);

#endif
