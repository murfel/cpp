#include <stdio.h>
#include "rectangle.h"

// TODO

Rectangle::Rectangle(int id, int x, int y, int width, int height) {
    set_id(id);
    set_x(x);
    set_y(y);
    set_width(width);
    set_height(height);
}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", get_id(), get_x(), get_y(), get_width(), get_height());
}

bool Rectangle::is_inside(int x, int y) const {
    if (x >= get_x() && x <= get_x() + width && y >= get_y() && y <= get_y() + height) {
        return true;
    }
    return false;
}

void Rectangle::zoom(int factor) {
    set_width(width * factor);
    set_height(height * factor);
}

int Rectangle::get_width() const { return width; }

int Rectangle::get_height() const { return height; }

void Rectangle::set_width(int width) { this->width = width; }

void Rectangle::set_height(int height) { this->height = height; }
