#ifndef _MATRIX_H_INCLUDED
#define _MATRIX_H_INCLUDED

#include <cstdio>
#include <cstddef>

#include <exception>
#include <string>

class Matrix {
public:
  Matrix(std::size_t rows, std::size_t cols);
  Matrix(const Matrix& other);
  ~Matrix();

  std::size_t rows() const;
  std::size_t cols() const;
  void set(std::size_t row, std::size_t col, int val);
  int get(std::size_t row, std::size_t col) const;

  Matrix& operator=(const Matrix& other);

  Matrix& operator+=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);

private:
  std::size_t _rows;
  std::size_t _cols;
  int **_data;
  void free_memory();
};


Matrix operator*(const Matrix& lhs, const Matrix& rhs);


class MatrixException : public std::exception {
  private:
    std::string error_msg;

  public:
    MatrixException(const char* msg) : error_msg(msg) {};
    ~MatrixException() throw() {};
    const char* what() const throw() { return this->error_msg.c_str(); };
};

#endif
