#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <iostream>

//using namespace std;

enum employees {DEVELOPER = 1, SALES_MANAGER};

class Employee {
public:
    virtual ~Employee();
    virtual int salary() const = 0;
    virtual std::ostream& print(std::ostream& os) const = 0;
    virtual std::ofstream& print(std::ofstream& ofs) const = 0;
    virtual std::istream& read(std::istream& is) = 0;
    virtual std::ifstream& read(std::ifstream& ifs) = 0;
    friend std::ostream& operator<<(std::ostream& os, const Employee& o);
    friend std::ofstream& operator<<(std::ofstream& ofs, const Employee& o);
    friend std::istream& operator>>(std::istream& is, Employee& o);
    friend std::ifstream& operator>>(std::ifstream& ifs, Employee& o);
protected:
    char *_name;
    int32_t _base_salary;
};


class Developer : public Employee {
public:
    Developer();
    int salary() const {
        int salary = _base_salary;
        if (_has_bonus) { salary += 1000; }
        return salary;
    }
    std::ostream& print(std::ostream& os) const;
    std::ofstream& print(std::ofstream& ofs) const;
    std::istream& read(std::istream& is);
    std::ifstream& read(std::ifstream& ifs);
    friend std::istream& operator>>(std::istream& is, Developer& o);
    friend std::ifstream& operator>>(std::ifstream& ifs, Developer& o);
private:
    Developer(const Developer&);
    Developer& operator=(Developer&);
    int32_t type;
    bool _has_bonus;
};


class SalesManager : public Employee {
public:
    SalesManager();
    int salary() const {
        return _base_salary + _sold_nm * _price * 0.01;
    }
    std::ostream& print(std::ostream& os) const;
    std::ofstream& print(std::ofstream& ofs) const;
    std::istream& read(std::istream& is);
    std::ifstream& read(std::ifstream& ifs);
    friend std::istream& operator>>(std::istream& is, SalesManager& o);
    friend std::ifstream& operator>>(std::ifstream& ifs, SalesManager& o);
private:
    SalesManager(const SalesManager&);
    SalesManager& operator=(SalesManager&);
    int32_t type;
    int32_t _sold_nm, _price;
};


class EmployeesArray {
public:
    EmployeesArray();
    ~EmployeesArray();
    void add(const Employee *e);
    int total_salary() const;
    friend std::ostream& operator<<(std::ostream& os, const EmployeesArray& o);
    friend std::ofstream& operator<<(std::ofstream& ofs, const EmployeesArray& o);
    friend std::ifstream& operator>>(std::ifstream& ifs, EmployeesArray& o);
private:
    Employee **_employees;
    int32_t _size;
    int32_t _capacity;
};


std::ostream& operator<<(std::ostream& os, Employee& o);
std::ofstream& operator<<(std::ofstream& ofs, Employee& o);

char * read_name(std::ifstream& ifs);

#endif
