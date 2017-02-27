#pragma once

#include "my_vector.h"

template <typename T>
void test_my_vector(T o1, T o2) {
    my_vector<T> v;
    assert(v.size() == 0);
    assert(v.empty());

    v.resize(2);
    v[0] = o1;
    v[1] = o2;
    assert(v[0] == o1);
    assert(v.size() == 2);
    assert(v.capacity() >= v.size());
    assert(!v.empty());

    size_t old_size = v.size();
    v.reserve(10);
    assert(v.capacity() >= 10);
    assert(v.size() == old_size);

    v.push_back(o1);
    assert(v[2] == o1);
    assert(v.size() == old_size + 1);

    v.pop_back();
    assert(v[0] == o1);
    assert(v[1] == o2);
    assert(v.size() == old_size);

    my_vector<T> v2(v);
    assert(v2[0] == o1);
    assert(v2[1] == o2);
    assert(v2.size() == v.size());

    v2.resize(3);
    v2[0] = o2;
    v2[1] = o1;
    v2[2] = o2;
    v = v2;
    assert(v[0] == v2[0]);
    assert(v[1] == v2[1]);
    assert(v[2] == v2[2]);

    v2.clear();
    assert(v2.empty());

    size_t size = 42;
    my_vector<T> v3(size);
    assert(v3.size() == size);

    v3[13] = o1;
    assert(v3[13] == o1);

    v3.resize(5);
    assert(v3.size() == 5);

    const T& elem = v[0];
    assert(elem == v[0]);
}
