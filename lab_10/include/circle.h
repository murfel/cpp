#pragma once

#include "figure.h"

class Circle : public Figure {
    public:
        Circle(int id, int x, int y, int radius, const char* label);
        ~Circle();
        void print() const;
        bool is_inside(int x, int y) const;
        void zoom(int factor);

        int get_radius() const;
        char* get_label() const;

        void set_radius(int radius);
        void set_label(const char* label);

    private:
        int radius;
        char* label;
};

