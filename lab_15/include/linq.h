#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>
#include <iostream>
#include <stdexcept>

using std::cerr;
using std::endl;

template<typename T, typename Iter>
class range_enumerator;
template<typename T>
class drop_enumerator;
template<typename T, typename U, typename F>
class select_enumerator;
template<typename T, typename F>
class until_enumerator;
template<typename T, typename F>
class where_enumerator;
template<typename T>
class take_enumerator;

template<typename T>
class enumerator {
public:
  virtual const T& operator*() = 0; // Получает текущий элемент.
  virtual enumerator<T>& operator++() = 0;  // Переход к следующему элементу
  virtual operator bool() = 0; // Возвращает true, если есть текущий элемент

  auto drop(int count) {
    return drop_enumerator<T>(*this, count);
  }

  template<typename U = T, typename F>
  auto select(F func) {
    return select_enumerator<U, T, F>(*this, std::move(func));
  }

  template<typename F>
  auto until(F func) {
    return until_enumerator<T, F>(*this, std::move(func));
  }

  auto until_eq(const T& value) {
    return until([&value](const T& x) { return x == value; });
  }

  template<typename F>
  auto where(F predicate) {
    return where_enumerator<T, F>(*this, std::move(predicate));
  }

  auto where_neq(const T& value) {
    return where([&value](const T& x) { return x != value; });
  }

  auto take(int count) {
    return take_enumerator<T>(*this, count);
  }

  std::vector<T> to_vector() {
    std::vector<T> result;
    while (*this) {
      result.push_back(**this);
      ++*this;
    }
    return result;
  }

  template<typename Iter>
  void copy_to(Iter it) {
    while (*this) {
      *it = **this;
      ++it;
      ++(*this);
    }
  }
};

template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
public:
  range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {
  }
  virtual const T& operator*() override {
    return *begin_;
  }
  virtual enumerator<T>& operator++() override {
    ++begin_;
    return *this;
  }
  virtual operator bool() override {
    return begin_!= end_;
  }

private:
  Iter begin_, end_;
};

template<typename Iter>
auto from(Iter begin, Iter end) {
  return range_enumerator<typename std::iterator_traits<Iter>::value_type, Iter>(begin, end);
}

template<typename T>
class drop_enumerator : public enumerator<T> {
public:
  drop_enumerator(enumerator<T> &parent, int count) : parent_(parent), count_(count) {}
  virtual const T& operator*() override {
    drop();
    if (count_)
      throw std::runtime_error("Attemp to dereference an empty Drop enumerator.");
    return *parent_;
  }
  virtual enumerator<T>& operator++() override {
    drop();
    if (count_)
      throw std::runtime_error("Attemp to increment past-the-end Drop enumerator.");
    ++parent_;
    return *this;
  }
  virtual operator bool() override {
    drop();
    return (count_ ? false : parent_);
  }
private:
  void drop() {
    while (parent_)
      if (count_) {
        ++parent_;
        --count_;
      }
      else
        break;
  }
  enumerator<T> &parent_;
  int count_;
};

template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
public:
  select_enumerator(enumerator<U> &parent, const F &func) : parent_(parent), func_(std::move(func)) {
    if (parent_)
      last_elem_ = func_(*parent_);
  }
  virtual const T& operator*() override {
    return last_elem_;
  }
  virtual select_enumerator& operator++() override {
    ++parent_;
    if (parent_)
      last_elem_ = func_(*parent_);
    return *this;
  }
  virtual operator bool() override {
    return parent_;
  }
private:
  enumerator<U> & parent_;
  F func_;
  T last_elem_;
};

template<typename T, typename F>
class until_enumerator : public enumerator<T> {
public:
  until_enumerator(enumerator<T> &parent, F predicate) : parent_(parent), predicate_(std::move(predicate)), is_valid_(*parent_ && !predicate_(*parent_)) {
  }
  virtual const T& operator*() override {
    return *parent_;
  }
  virtual enumerator<T>& operator++() override {
    ++parent_;
    is_valid_ = !predicate_(*parent_);
    return *this;
  }
  virtual operator bool() override {
    return parent_ && is_valid_;
  }
private:
  enumerator<T> &parent_;
  F predicate_;
  bool is_valid_;
};

template<typename T, typename F>
class where_enumerator : public enumerator<T> {
public:
  // инвариант: текущий элемент корректен (если не конец последовательности)
  where_enumerator(enumerator<T> &parent, F predicate) : parent_(parent), predicate_(std::move(predicate)) {
    advance();
  }
  virtual const T& operator*() override {
    operator bool();
    return *parent_;
  }
  virtual enumerator<T>& operator++() override {
    ++parent_;
    advance();
    return *this;
  }
  virtual operator bool() override {
    return parent_ && predicate_(*parent_);
  }
private:
  void advance() {
    while (parent_ && !predicate_(*parent_))
      ++parent_;
  }
  enumerator<T> &parent_;
  F predicate_;
};

template<typename T>
class take_enumerator : public enumerator<T> {
public:
  take_enumerator(enumerator<T> &parent, int count) : parent_(parent), count_(count) {}
  virtual const T& operator*() override {
    return *parent_;
  }
  virtual enumerator<T>& operator++() override {
    ++parent_;
    --count_;
    return *this;
  }
  virtual operator bool() override {
    return count_ && parent_;
  }
private:
  enumerator<T> &parent_;
  int count_;
};


#endif
