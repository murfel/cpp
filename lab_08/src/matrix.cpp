#include "matrix.h"

void Matrix::init(std::size_t r, std::size_t c) {
  _rows = r;
  _cols = c;
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

Matrix::Matrix(const Matrix& m) {
  init(m.get_rows(), m.get_cols());
  for (size_t i = 0; i < _rows; i++) {
    for (size_t j = 0; j < _cols; j++) {
      _data[i][j] = m.get(i, j);
    }
  }
}

Matrix::~Matrix() {
  delete _data[0];
  delete _data;
}

std::size_t Matrix::get_rows() const { return _rows; }
std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
  _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
  return _data[i][j];
}

void Matrix::print(FILE* f) const {
  for (size_t i = 0; i < _rows; i++) {
    for (size_t j = 0; j < _cols; j++) {
      fprintf(f, "%d ", _data[i][j]);
    }
    fprintf(f, "\n");
  }
}

Matrix& Matrix::operator=(const Matrix& m) {
  delete _data[0];
  delete _data;
  init(m.get_rows(), m.get_cols());
  for (size_t i = 0; i < _rows; i++) {
    for (size_t j = 0; j < _cols; j++) {
      _data[i][j] = m.get(i, j);
    }
  }
  return *this;
}

bool Matrix::operator==(const Matrix& m) const {
  if (_rows != m.get_rows()) {
    return false;
  }
  if (_cols != m.get_cols()) {
    return false;
  }
  for (size_t i = 0; i < _rows; i++) {
    for (size_t j = 0; j < _cols; j++) {
      if (_data[i][j] != m.get(i, j)) {
        return false;
      }
    }
  }
  return true;
}

bool Matrix::operator!=(const Matrix& m) const {
  return !operator==(m);
}

Matrix& Matrix::operator+=(const Matrix& m) {
  for (size_t i = 0; i < _rows; i++) {
    for (size_t j = 0; j < _cols; j++) {
      _data[i][j] += m.get(i, j);
    }
  }
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
  for (size_t i = 0; i < _rows; i++) {
    for (size_t j = 0; j < _cols; j++) {
      _data[i][j] -= m.get(i, j);
    }
  }
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
  Matrix result = operator*(m);
  for (size_t i = 0; i < _rows; i++) {
    for (size_t j = 0; j < _cols; j++) {
      _data[i][j] = result.get(i, j);
    }
  }
  return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
  Matrix result = Matrix(*this);
  result += m;
  return result;
}

Matrix Matrix::operator-(const Matrix& m) const {
  Matrix result = Matrix(*this);
  result += m;
  return result;
}

Matrix Matrix::operator*(const Matrix& m) const {
  Matrix result = Matrix(_rows, m.get_cols());
  for (size_t i = 0; i < _rows; i++) {
    for (size_t j = 0; j < _cols; j++) {
      result.set(i, j, 0);
      for (size_t t = 0; t < _cols; t++) {
        result.set(i, j, result.get(i, j) + _data[i][t] * m.get(t, j));
      }
    }
  }
  return result;
}
