#include <iostream>
#include <string>

#include "my_vector.h"

class Product {
public:
    Product(const char* name, int quantity, double price) : name_((char *)name), quantity_(quantity), price_(price) { }
    std::string name() const {
        return std::string(name_);
    }
    int quantity() const {
        return quantity_;
    }
    double price() const {
        return price_;
    }
private:
    char *name_;
    int quantity_;
    double price_;
};

std::ostream& operator<<(std::ostream& os, Product& o) {
    os << o.name() << " ";
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

