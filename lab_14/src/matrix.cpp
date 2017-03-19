#include "matrix.h"

void Matrix::init(std::size_t r, std::size_t c) {
  _rows = r;
  _cols = c;
  if (r == 0 || c == 0) {
    _data = NULL;
    return;
  }
  _data = new int*[_rows];
  int * temp = new int[_rows * _cols];
  for (size_t i = 0; i < _rows; i++) {
    _data[i] = temp + i * _cols;
  }
  for (size_t i = 0; i < _rows; i++) {
    for (size_t j = 0; j < _cols; j++) {
      _data[i][j] = 0;
    }
  }
}

Matrix::Matrix(std::size_t r, std::size_t c) {
  init(r, c);
}

Matrix::Matrix(const Matrix& other) {
  init(other.get_rows(), other.get_cols());
  for (size_t i = 0; i < _rows; i++) {
    for (size_t j = 0; j < _cols; j++) {
      _data[i][j] = other.get(i, j);
    }
  }
}

void Matrix::free_memory() {
  if (_rows != 0 && _cols != 0) {
    delete[] _data[0];
    delete[] _data;
  }
}

Matrix::~Matrix() {
  free_memory();
}

std::size_t Matrix::get_rows() const { return _rows; }
std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
  _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
  if (i >= _rows || j >= _cols) {
    throw MatrixException("ACCESS: bad index.");
  }
  return _data[i][j];
}

Matrix& Matrix::operator=(const Matrix& other) {
  free_memory();
  init(other.get_rows(), other.get_cols());
  for (size_t i = 0; i < _rows; i++) {
    for (size_t j = 0; j < _cols; j++) {
      _data[i][j] = other.get(i, j);
    }
  }
  return *this;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  if (_rows != other.get_rows() || _cols != other.get_cols()) {
    throw MatrixException("ADD: dimensions do not match");
  }
  for (size_t i = 0; i < _rows; i++) {
    for (size_t j = 0; j < _cols; j++) {
      _data[i][j] += other.get(i, j);
    }
  }
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  *this = operator*(other);
  return *this;
}

Matrix Matrix::operator*(const Matrix& other) const {
  if (_cols != other.get_rows()) {
    throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
  }
  Matrix result = Matrix(_rows, other.get_cols());
  for (size_t i = 0; i < _rows; i++) {
    for (size_t j = 0; j < _cols; j++) {
      result.set(i, j, 0);
      for (size_t t = 0; t < _cols; t++) {
        result.set(i, j, result.get(i, j) + _data[i][t] * other.get(t, j));
      }
    }
  }
  return result;
}
