#pragma once

#include "figure.h"

class Rectangle : public Figure {
    public:
        Rectangle(int id, int x, int y, int width, int height);
        void print() const;
        bool is_inside(int x, int y) const;
        void zoom(int factor);

        int get_width() const;
        int get_height() const;

        void set_width(int width);
        void set_height(int height);

    private:
        int width, height;
};
