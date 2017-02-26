#pragma once

#include <cstddef>
#include <cassert>
#include <iostream>
#include <typeinfo>
#include <new>

template <class T>
class my_vector{
public:
    my_vector();
    my_vector(size_t n);
    my_vector(my_vector& other);
    my_vector& operator=(my_vector& other);
    ~my_vector();

    size_t size() const;
    size_t capacity() const;
    bool empty() const;

    void resize(size_t n);
    void reserve(size_t n);

    T& operator[](size_t index) const;
    T& operator[](size_t index);

    void push_back(const T& t);
    void pop_back();
    void clear();

private:
    size_t capacity_;
    size_t size_;
    T* array_;
    static const int INIT_CAPACITY = 4;
    static size_t round_up_2(size_t n);
    void init(size_t n);
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
        os << o[i] << " ";
    }
    return os;
}

template <class T>
void my_vector<T>::init(size_t n) {
    size_ = n;
    capacity_ = (size_ == 0) ? INIT_CAPACITY : round_up_2(size_);
    array_ = static_cast<T*>(operator new[] (capacity_ * sizeof(T)));
    for (size_t i = 0; i < size_; i++) {
        new (array_ + i) T();
    }
}

template <class T>
my_vector<T>::my_vector() {
    init(0);
}

template <class T>
my_vector<T>::my_vector(size_t n) {
    init(n);
}

template <class T>
my_vector<T>::my_vector(my_vector& other) {
    size_ = other.size();
    capacity_ = (size_ == 0) ? INIT_CAPACITY : round_up_2(size_);
    array_ = static_cast<T*>(operator new[] (capacity_ * sizeof(T)));
    for (size_t i = 0; i < size_; i++) {
        new (array_ + i) T(other[i]);
    }
}

template <class T>
my_vector<T>& my_vector<T>::operator=(my_vector& other) {
    resize(other.size());
    for (size_t i = 0; i < size_; i++) {
        array_[i] = other[i];
    }
    return *this;
}

template <class T>
my_vector<T>::~my_vector() {
    for (size_t i = 0; i < size_; i++) {
        array_[i].~T();
    }
    delete[] array_;
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
    for (size_t i = size_; i < n; i++) {
        new (array_ + i) T();
    }
    size_ = n;
}

template <class T>
void my_vector<T>::reserve(size_t n) {
    if (capacity_ < n) {
        capacity_ = round_up_2(n);
        T* temp = static_cast<T*> (operator new[] (capacity_ * sizeof(T)));
        for (size_t i = 0; i < size_; i++) {
            new (temp + i) T(array_[i]);
            array_[i].~T();
        }
        delete[] array_;
        array_ = temp;
    }
}

template <class T>
T& my_vector<T>::operator[](size_t index) const {
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
