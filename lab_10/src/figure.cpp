#include "figure.h"

// TODO

Figure::Figure() {
    ;
}
Figure::~Figure() {
    ;
}

Figure::Figure(int id, int x, int y) {
    set_id(id);
    set_x(x);
    set_y(y);
}

void Figure::move(int new_x, int new_y) {
    x = new_x;
    y = new_y;
}

int Figure::get_id() const { return id; }
int Figure::get_x() const { return x; }
int Figure::get_y() const { return y; }

void Figure::set_id(int id) { this->id = id; }
void Figure::set_x(int x) { this->x = x; }
void Figure::set_y(int y) { this->y = y; }
