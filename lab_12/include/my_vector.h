#include <cstddef>
#include <iostream>
#include <typeinfo>
#include <cassert>

#define INIT_CAPACITY 4

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

    void push_back(T& t);
    void pop_back();
    void clear();

private:
    size_t capacity_;
    size_t size_;
    T* array_;
    void init(size_t n);
};

size_t round(size_t n) {
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
    capacity_ = (n == 0) ? INIT_CAPACITY : round(n);
    array_ = (T*)new char [capacity_ * sizeof(T)];
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
    init(other.size());
    for (size_t i = 0; i < size_; i++) {
        array_[i] = other[i];
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
    size_ = n;
}

template <class T>
void my_vector<T>::reserve(size_t n) {
    if (capacity_ < n) {
        capacity_ = round(n);
        T* temp = (T*)new char [capacity_ * sizeof(T)];
        for (size_t i = 0; i < size_; i++) {
            temp[i] = array_[i];
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
void my_vector<T>::push_back(T& t) {
    resize(size_ + 1);
    array_[size_ - 1] = t;
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

template <typename T>
void test_my_vector(T o1, T o2) {
    assert(round(1) == 1);
    assert(round(4) == 4);
    assert(round(5) == 8);

    my_vector<T> v;
    assert(v.size() == 0);
    assert(v.empty());

    v.resize(2);
    v[0] = o1;
    v[1] = o2;
    assert(v.size() == 2);
    assert(v.capacity() >= v.size());
    assert(!v.empty());

    size_t old_size = v.size();
    v.reserve(10);
    assert(v.capacity() >= 10);
    assert(v.size() == old_size);

    v.push_back(o1);
    assert(v.size() == old_size + 1);

    v.pop_back();
    assert(v.size() == old_size);

    my_vector<T> v2(v);
    assert(v2.size() == v.size());

    v2.clear();
    assert(v2.empty());
}
