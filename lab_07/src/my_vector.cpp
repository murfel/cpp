#include <cassert>
#include <algorithm>
#include "my_vector.h"

#define START_CAPACITY 2
#define TYPE int

MyVector::MyVector() {
    _data = new int[START_CAPACITY];
    _sz = 0;
    _cp = START_CAPACITY;
}

MyVector::MyVector(std::size_t init_capacity) {
    _data = new int[init_capacity];
    _sz = 0;
    _cp = init_capacity;
}

MyVector::~MyVector() {
    delete []_data;
}

void MyVector::set(std::size_t index, int value) {
    assert(index < _sz);
    _data[index] = value;
}

int MyVector::get(std::size_t index) {
    assert(index < _sz);
    return _data[index];
}

std::size_t MyVector::size() {
    return _sz;
}

std::size_t MyVector::capacity() {
    return _cp;
}

void MyVector::reserve(std::size_t new_capacity) {
    if (new_capacity > _cp) {
        int * temp = _data;
        _data = new int[new_capacity];
        std::copy(temp, temp + _sz, _data);
        delete []temp;
        _cp = new_capacity;
    }
}

void MyVector::resize(std::size_t new_size) {
    if (new_size > _sz) {
        this->reserve(new_size);
        std::fill(_data + _sz, _data + new_size, 0);
        _sz = new_size;
    }
}

void MyVector::push_back(int value) {
    if (_sz == _cp) {
        this->reserve(_cp * 2);
    }
    _sz++;
    this->set(_sz - 1, value);
}

void MyVector::insert(std::size_t index, int value) {
    if (index < _sz) {
        this->push_back(value);
        for (size_t i = _sz - 1; i > index; i--) {
            std::swap(_data[i], _data[i - 1]);
        }
    }
    else {
        this->resize(index + 1);
        this->set(index, value);
    }
}

void MyVector::erase(std::size_t index) {
    assert(index < _sz);
    for (size_t i = index; i < _sz - 1; i++) {
        std::swap(_data[i], _data[i + 1]);
    }
    _sz--;
}
