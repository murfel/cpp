#include <cstddef>
#include <iostream>
#include <typeinfo>

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
    capacity_ = (n == 0) ? INIT_CAPACITY : round(capacity_);
    array_ = new T [capacity_];
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
    for (int i = 0; i < size_; i++) {
        array_[i] = other[i];
    }
}

template <class T>
my_vector<T>& my_vector<T>::operator=(my_vector& other) {
    resize(other.size());
    for (int i = 0; i < size_; i++) {
        array_[i] = other[i];
    }
}

template <class T>
my_vector<T>::~my_vector() {
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
        T* temp = new T [round(n)];
        for (int i = 0; i < size_; i++) {
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
}

template <class T>
void my_vector<T>::clear() {
    while (size_--) {
        delete array_[size_ - 1];
    }
}

template <class T>
void test_my_vector<T>(T& o1, T& o2) {
    v = my_vector<T>();
    assert v.size() == 0;
}
