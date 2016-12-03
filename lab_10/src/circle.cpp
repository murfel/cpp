#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include "circle.h"

Circle::Circle(int id, int x, int y, int radius, const char* label) {
    set_id(id);
    set_x(x);
    set_y(y);
    set_radius(radius);
    this->label = new char[1];
    set_label(label);
}

Circle::~Circle() {
    delete [] this->label;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", get_id(), get_x(), get_y(), get_radius(), get_label());
}

bool Circle::is_inside(int x, int y) const {
    if (abs(get_x() - x) <= get_radius() && abs(get_y() - y) <= get_radius()) {
        return true;
    }
    return false;
}

void Circle::zoom(int factor) {
    set_radius(get_radius() * factor);
}

int Circle::get_radius() const { return radius; }

char* Circle::get_label() const { return label; }

void Circle::set_radius(int radius) { this->radius = radius; }

void Circle::set_label(const char* label) {
    delete [] this->label;
    this->label = new char[strlen(label) + 1];
    strcpy(this->label, label);
}
