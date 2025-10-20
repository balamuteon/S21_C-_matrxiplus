#include "s21_matrix_oop.h"

/**
 * @brief Copy assignment operator.
 * @details
 * This operator is responsible for copying the contents of the other matrix
 * to the current one. The function first checks if the two matrices are the
 * same object and if so, returns the current matrix immediately. Otherwise,
 * it creates a temporary matrix with the same dimensions as the other matrix,
 * copies the values from the other matrix to the temporary matrix, and then
 * moves the temporary matrix to the current matrix.
 * @param other The matrix to copy from.
 * @return A reference to the current matrix.
 */
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this == &other) {
    return *this;
  }

  S21Matrix temp(other.rows_, other.cols_);
  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      temp.matrix_[i][j] = other.matrix_[i][j];
    }
  }

  *this = std::move(temp);

  return *this;
}

/**
 * @brief Move assignment operator.
 * @details
 * This operator is responsible for moving the contents of the other matrix
 * to the current one. The function first releases the memory of the current
 * matrix, then copies the rows, columns and matrix pointer of the other matrix
 * to the current matrix and finally sets the other matrix's pointer to nullptr.
 * @param other The matrix to move from.
 * @return A reference to the current matrix.
 * @note This function is noexcept.
 */
S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;

    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;

    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

/**
 * @brief Returns a reference to the element at the given row and column.
 * @details
 * This method allows to access the elements of the matrix by their row and
 * column indices.
 * @param row The row index of the element.
 * @param col The column index of the element.
 * @return A reference to the element at the given row and column.
 * @throw std::out_of_range if the row or column index is out of range.
 */
double& S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Index out of range.");
  }
  return matrix_[row][col];
}

/**
 * @brief Returns a constant reference to the element at the given row and
 * column.
 * @details
 * This method allows for read-only access to the elements of the matrix by
 * their row and column indices. It ensures that the requested indices are
 * within the valid range and throws an exception if they are not.
 * @param row The row index of the element.
 * @param col The column index of the element.
 * @return A constant reference to the element at the given row and column.
 * @throw std::out_of_range if the row or column index is out of range.
 */
const double& S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Index out of range.");
  }
  return matrix_[row][col];
}

/**
 * @brief Compares two matrices for equality.
 *
 * This operator checks if the current matrix is equal to another matrix
 * by comparing their dimensions and elements. It utilizes the EqMatrix
 * method to perform the comparison, ensuring that both matrices have the
 * same size and corresponding elements are equal within a tolerance.
 *
 * @param other The matrix to compare against the current matrix.
 * @return true if the matrices are equal; false otherwise.
 */
bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

/**
 * @brief Calculates the sum of the current matrix and another matrix.
 *
 * This operator adds another matrix to the current matrix and returns the
 * result. The operation is performed by calling the SumMatrix method, which
 * takes care of checking the dimensions of both matrices and performing the
 * element-wise addition.
 *
 * @param other The matrix to add to the current matrix.
 * @return The sum of the two matrices.
 */
S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

/**
 * @brief Calculates the difference of the current matrix and another matrix.
 *
 * This operator subtracts another matrix from the current matrix and returns
 * the result. The operation is performed by calling the SubMatrix method,
 * which takes care of checking the dimensions of both matrices and performing
 * the element-wise subtraction.
 *
 * @param other The matrix to subtract from the current matrix.
 * @return The difference of the two matrices.
 */
S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

/**
 * @brief Calculates the product of the current matrix and another matrix.
 *
 * This operator multiplies another matrix by the current matrix and returns
 * the result. The operation is performed by calling the MulMatrix method,
 * which takes care of checking the dimensions of both matrices and performing
 * the matrix product.
 *
 * @param other The matrix to multiply the current matrix by.
 * @return The product of the two matrices.
 */
S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

/**
 * @brief Scales the current matrix by a given number.
 *
 * This operator multiplies every element of the current matrix by the given
 * number and returns the result. The operation is performed by calling the
 * MulNumber method, which takes care of performing the element-wise scalar
 * multiplication.
 *
 * @param num The number to scale the current matrix by.
 * @return The scaled matrix.
 */
S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

/**
 * @brief Subtracts the given matrix from the current matrix.
 *
 * This operator subtracts another matrix from the current matrix and returns
 * the result. The operation is performed by calling the SubMatrix method,
 * which takes care of checking the dimensions of both matrices and performing
 * the element-wise subtraction.
 *
 * @param other The matrix to subtract from the current matrix.
 * @return The difference of the two matrices.
 */
S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

/**
 * @brief Scales the current matrix by a given number in place.
 *
 * This operator multiplies every element of the current matrix by the given
 * number. The operation is performed by calling the MulNumber method, which
 * takes care of performing the element-wise scalar multiplication in place.
 *
 * @param num The number to scale the current matrix by.
 * @return The current matrix.
 */
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

/**
 * @brief Calculates the difference of the current matrix and another matrix in
 * place.
 *
 * This operator subtracts another matrix from the current matrix and assigns
 * the result to the current matrix. The operation is performed by calling the
 * SubMatrix method, which takes care of checking the dimensions of both
 * matrices and performing the element-wise subtraction in place.
 *
 * @param other The matrix to subtract from the current matrix.
 * @return The current matrix.
 */
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

/**
 * @brief Multiplies the current matrix by another matrix in place.
 *
 * This operator multiplies the current matrix by another matrix and assigns the
 * result to the current matrix. The operation is performed by calling the
 * MulMatrix method, which takes care of checking the dimensions of both
 * matrices and performing the matrix product in place.
 *
 * @param other The matrix to multiply the current matrix by.
 * @return The current matrix.
 */
S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}