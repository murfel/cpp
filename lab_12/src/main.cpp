#include <iostream>
#include <string>
#include <cstring>

#include "my_vector.h"
#include "test.h"

class Product {
public:
    Product() : name_(NULL), quantity_(0), price_(0) { };
    Product(const char* name, int quantity, double price) : quantity_(quantity), price_(price) {
        set_name(name);
    }
    Product(const Product& o) : quantity_(o.quantity()), price_(o.price()) {
        set_name(o.name());
    }
    Product& operator=(const Product& other) {
        if (this != &other) {
            delete[] name_;
            set_name(other.name());
            quantity_ = other.quantity();
            price_ = other.price();
        }
        return *this;
    }
    ~Product() {
        delete[] name_;
    }
    const char* name() const {
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
    void set_name(const char* name) {
        if (name) {
            name_ = new char [strlen(name) + 1];
            strcpy(name_, name);
        }
        else {
            name_ = NULL;
        }
    }
};

std::ostream& operator<<(std::ostream& os, const Product& o) {
    os << std::string(o.name()) << " ";
    os << o.quantity() << " ";
    os << o.price();
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
