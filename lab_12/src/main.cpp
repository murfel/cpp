#include <iostream>
#include <string>
#include <cstring>

#include "my_vector.h"
#include "test.h"

class Product {
public:
    void copy_name(const char* name) {
        if (name) {
            name_ = new char [strlen(name) + 1];
            strcpy(name_, name);
        }
        else {
            name_ = NULL;
        }
    }
    Product() : name_(NULL), quantity_(0), price_(0) { };
    Product(const char* name, int quantity, double price) : quantity_(quantity), price_(price) {
        copy_name(name);
    }
    Product(const Product& o) : quantity_(o.quantity()), price_(o.price()) {
        copy_name(o.name());
    }
    ~Product() {
        delete[] name_;
    }
    char* name() const {
        return name_;
    }
    int quantity() const {
        return quantity_;
    }
    double price() const {
        return price_;
    }
    bool operator==(const Product &o) const {
        return (strcmp(name_, o.name()) == 0) && (quantity_ == o.quantity()) && (price_ == o.price());
    }
private:
    char *name_;
    int quantity_;
    double price_;
};

std::ostream& operator<<(std::ostream& os, Product& o) {
    os << std::string(o.name()) << " ";
    os << o.quantity() << " ";
    os << o.price() << " ";
    return os;
}

void print(const my_vector<Product>& v) {
    std::cout << v << std::endl;
}

int main() {
    test_my_vector<int>(5, 10);
    test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));

    return 0;
}
