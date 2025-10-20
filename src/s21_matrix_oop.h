#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  void AllocateMatrix();

 public:
  // -- Constructors, destructor --

  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  // --- Getters ---

  int get_rows() const;
  int get_cols() const;

  // --- Setters ---
  void set_rows(int new_rows);
  void set_cols(int new_cols);

  // --- Accessors, mutatators ---

  double& operator()(int row, int col);
  const double& operator()(int row, int col) const;

  // --- Assignment operators ---

  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;

  // --- Overload operators ---

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  bool operator==(const S21Matrix& other) const;

  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);

  // --- Public methods ---

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  // --- Other methods ---

  void printMatrix() const;
};

#endif  // S21_MATRIX_OOP_H