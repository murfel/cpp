#pragma once

class Figure {
  public:
    Figure();
    Figure(int id, int x, int y);
    virtual ~Figure();

    virtual void print() const = 0;
    virtual bool is_inside(int x, int y) const = 0;
    virtual void zoom(int factor) = 0;
    void move(int new_x, int new_y);

    int get_id() const;
    int get_x() const;
    int get_y() const;

    void set_id(int id);
    void set_x(int x);
    void set_y(int y);

  protected:
    int id;
    int x;
    int y;
};
