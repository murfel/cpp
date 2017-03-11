#pragma once

#include <cstddef>
#include <cassert>
#include <cstdint>

template<typename T, std::size_t N>
class my_array {
public:
  T& at(std::size_t index) {
    assert(index < N);
    return array_[index];
  }
  const T& at(std::size_t index) const {
    assert(index < N);
    return array_[index];
  }
  T& operator[](std::size_t index) {
    return array_[index];
  }
  const T& operator[](std::size_t index) const {
    return array_[index];
  }

  bool empty() const {
    return N == 0;
  }
  std::size_t size() const {
    return N;
  }

  void fill(const T& val) {
    for (std::size_t i = 0; i < N; ++i) {
      array_[i] = val;
    }
  }
private:
  T array_[N];
};



template<std::size_t N>
class my_array<bool, N> {
private:
  class Proxy {
  public:
    Proxy(uint8_t& data, std::size_t short_index) : data_(data), short_index_(short_index) {}
    operator bool() const {
      return (data_ >> short_index_) & 1;
    }
    Proxy& operator=(const bool val) {
      data_ = data_ & ~(1 << short_index_);
      data_ = data_ | ((uint8_t)val << short_index_);
      return *this;
    }
    Proxy& operator=(const Proxy& o) {
      if (o != *this) {
        *this = bool(o);
      }
      return *this;
    }
  private:
    uint8_t& data_;
    std::size_t short_index_;
  };

public:
  my_array();
  my_array(const my_array<bool, N>& o) {
    for (std::size_t i = 0; i < N; i++) {
      (*this)[i] = o[i];
    }
  }
  Proxy at(std::size_t index) {
    assert(index < N);
    return Proxy(array_[index / 8], index % 8);
  }
  const Proxy at(std::size_t index) const {
    assert(index < N);
    return Proxy(array_[index / 8], index % 8);
  }
  Proxy operator[](std::size_t index) {
    return Proxy(array_[index / 8], index % 8);
  }
  const Proxy operator[](std::size_t index) const {
    return Proxy(array_[index / 8], index % 8);
  }

  bool empty() const {
    return N == 0;
  }
  std::size_t size() const {
    return N;
  }

  void fill(const bool val) {
    uint8_t wide_val = 0;
    if (val) {
      wide_val = ~wide_val;
    }
    for (std::size_t i = 0; i < (N + 7) / 8; i++) {
      array_[i] = wide_val;
    }
  }
private:
  uint8_t array_[(N + 7) / 8];
};
