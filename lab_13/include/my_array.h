#pragma once

#include <cassert>
#include <climits>
#include <cstddef>
#include <cstring>


template<typename T, std::size_t N>
class my_array {
public:
  T& operator[](std::size_t index) {
    return array_[index];
  }
  const T& operator[](std::size_t index) const {
    return array_[index];
  }
  T& at(std::size_t index) {
    assert(index < N);
    return operator[](index);
  }
  const T& at(std::size_t index) const {
    assert(index < N);
    return operator[](index);
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
  class proxy {
  public:
    proxy(unsigned char& data, std::size_t short_index) : data_(data), short_index_(short_index) {}
    operator bool() const {
      return (data_ >> short_index_) & 1;
    }
    proxy& operator=(const bool val) {
      data_ &= ~(1 << short_index_);
      data_ |= ((unsigned char)val << short_index_);
      return *this;
    }
    proxy& operator=(const proxy& o) {
      return *this = bool(o);
    }
  private:
    unsigned char& data_;
    std::size_t short_index_;
  };

public:
  my_array() {
    memset(array_, 0, blocks_);
  }

  proxy operator[](std::size_t index) {
    return proxy(array_[get_block(index)], get_position(index));
  }
  bool operator[](std::size_t index) const {
    return (array_[get_block(index)] >> get_position(index)) & 1;
  }
  proxy at(std::size_t index) {
    assert(index < N);
    return operator[](index);
  }
  bool at(std::size_t index) const {
    assert(index < N);
    return operator[](index);
  }

  bool empty() const {
    return N == 0;
  }
  std::size_t size() const {
    return N;
  }

  void fill(const bool val) {
    memset(array_, val ? ~0 : 0, blocks_);
  }
private:
  static const std::size_t blocks_ = (N - 1 + CHAR_BIT) / CHAR_BIT;
  unsigned char array_[blocks_];

  std::size_t get_block(std::size_t index) const {
    return index / CHAR_BIT;
  }

  std::size_t get_position(std::size_t index) const {
    return index % CHAR_BIT;
  }
};
