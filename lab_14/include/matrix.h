#ifndef _MATRIX_H_INCLUDED
#define _MATRIX_H_INCLUDED

#include <cstdio>
#include <cstddef>

#include <exception>
#include <string>

class Matrix {
public:
  Matrix(std::size_t r, std::size_t c);
  Matrix(const Matrix& m);
  ~Matrix();

  std::size_t get_rows() const;
  std::size_t get_cols() const;
  void set(std::size_t i, std::size_t j, int val);
  int get(std::size_t i, std::size_t j) const;

  Matrix& operator=(const Matrix& m);

  Matrix operator*(const Matrix& m) const;

  Matrix& operator+=(const Matrix& m);
  Matrix& operator*=(const Matrix& m);

  Matrix& operator[](std::size_t i);
  const Matrix& operator[](std::size_t i) const;

private:
  std::size_t _rows;
  std::size_t _cols;
  int **_data;
  void init(std::size_t r, std::size_t c);
};


class MatrixException : public std::exception {
  private:
    std::string error_msg;

  public:
    MatrixException(const char* msg) : error_msg(msg) {};
    ~MatrixException() throw() {};
    const char* what() const throw() { return this->error_msg.c_str(); };
};

#endif
