#pragma once

#include <cstddef>
#include <cassert>
#include <iostream>
#include <typeinfo>
#include <new>

template <class T>
class my_vector{
public:
    my_vector(size_t n = 0);
    my_vector(const my_vector& other);
    my_vector& operator=(const my_vector& other);
    ~my_vector();

    size_t size() const;
    size_t capacity() const;
    bool empty() const;

    void resize(size_t n);
    void reserve(size_t n);

    const T& operator[](size_t index) const;
    T& operator[](size_t index);

    void push_back(const T& t);
    void pop_back();
    void clear();

private:
    size_t capacity_;
    size_t size_;
    T* array_;
    static const int INIT_CAPACITY = 1;
    static size_t round_up_2(size_t n);
};

template <class T>
size_t my_vector<T>::round_up_2(size_t n) {
    size_t rounded = 1;
    while (rounded < n) {
        rounded *= 2;
    }
    return rounded;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const my_vector<T>& o) {
    for (size_t i = 0; i < o.size(); i++) {
        os << o[i];
        if (i != o.size() - 1) {
            os << " ";
        }
    }
    return os;
}

template <class T>
my_vector<T>::my_vector(size_t n) : size_(n) {
    capacity_ = (size_ == 0) ? INIT_CAPACITY : round_up_2(size_);
    array_ = static_cast<T*>(operator new[] (capacity_ * sizeof(T)));
    for (size_t i = 0; i < size_; i++) {
        new (array_ + i) T();
    }
}

template <class T>
my_vector<T>::my_vector(const my_vector& other) : size_(other.size()) {
    capacity_ = (size_ == 0) ? INIT_CAPACITY : round_up_2(size_);
    array_ = static_cast<T*>(operator new[] (capacity_ * sizeof(T)));
    for (size_t i = 0; i < size_; i++) {
        new (array_ + i) T(other[i]);
    }
}

template <class T>
my_vector<T>& my_vector<T>::operator=(const my_vector& other) {
    if (this != &other) {
        clear();
        reserve(other.size());
        size_ = other.size();
        for (size_t i = 0; i < size_; i++) {
            new (array_ + i) T(other[i]);
        }
    }
    return *this;
}

template <class T>
my_vector<T>::~my_vector() {
    for (size_t i = 0; i < size_; i++) {
        array_[i].~T();
    }
    operator delete[] (array_);
}

template <class T>
size_t my_vector<T>::size() const {
    return size_;
}

template <class T>
size_t my_vector<T>::capacity() const {
    return capacity_;
}

template <class T>
bool my_vector<T>::empty() const {
    return size_ == 0;
}

template <class T>
void my_vector<T>::resize(size_t n) {
    reserve(n);
    if (n < size_) {
        for (size_t i = n; i < size_; i++) {
            array_[i].~T();
        }
    }
    else {
        for (size_t i = size_; i < n; i++) {
            new (array_ + i) T();
        }
    }
    size_ = n;
}

template <class T>
void my_vector<T>::reserve(size_t n) {
    if (capacity_ < n) {
        capacity_ = round_up_2(n);
        T* new_array = static_cast<T*> (operator new[] (capacity_ * sizeof(T)));
        for (size_t i = 0; i < size_; i++) {
            new (new_array + i) T(array_[i]);
            array_[i].~T();
        }
        operator delete[] (array_);
        array_ = new_array;
    }
}

template <class T>
const T& my_vector<T>::operator[](size_t index) const {
    return array_[index];
}

template <class T>
T& my_vector<T>::operator[](size_t index) {
    return array_[index];
}

template <class T>
void my_vector<T>::push_back(const T& t) {
    reserve(size_ + 1);
    new (array_ + size_) T(t);
    size_++;
}

template <class T>
void my_vector<T>::pop_back() {
    size_--;
    array_[size_].~T();
}

template <class T>
void my_vector<T>::clear() {
    for (size_t i = 0; i < size_; i++) {
        array_[i].~T();
    }
    size_ = 0;
}
