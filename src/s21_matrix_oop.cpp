#include "s21_matrix_oop.h"

// --- Base methods ---

/**
 * @brief Compares this matrix with another matrix for equality.
 *
 * This function checks if the dimensions of the two matrices are the same.
 * If they are, it compares each corresponding element of the matrices
 * to ensure they are equal within a tolerance of 1e-7.
 *
 * @param other The matrix to compare with this matrix.
 * @return true if the matrices are equal in dimensions and elements;
 * false otherwise.
 */
bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
        return false;
      }
    }
  }
  return true;
}

/**
 * @brief Adds the elements of another matrix to this matrix.
 *
 * This function checks if the dimensions of the two matrices are the same.
 * If they are, it adds each corresponding element of the other matrix to
 * this matrix. If the dimensions differ, it throws an exception.
 *
 * @param other The matrix whose elements are to be added to this matrix.
 * @exception std::invalid_argument Thrown if the matrices have different
 * dimensions.
 */
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrices have different dimensions for SumMatrix.");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

/**
 * @brief Subtracts the elements of another matrix from this matrix.
 *
 * This function checks if the dimensions of the two matrices are the same.
 * If they are, it subtracts each corresponding element of the other matrix
 * from this matrix. If the dimensions differ, it throws an exception.
 *
 * @param other The matrix whose elements are to be subtracted from this matrix.
 * @exception std::invalid_argument Thrown if the matrices have different
 * dimensions.
 */
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrices have different dimensions for SubMatrix.");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

/**
 * @brief Multiplies all elements of the matrix by a given number.
 *
 * The function multiplies each element of the matrix by the given number.
 *
 * @param num The number to multiply the elements of the matrix by.
 */
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

/**
 * @brief Multiplies the matrix by another matrix.
 *
 * The function checks if the dimensions of the two matrices are suitable for
 * multiplication. If they are, it multiplies the two matrices and stores the
 * result in the current matrix. If the dimensions differ, it throws an
 * exception.
 *
 * @param other The matrix to multiply the current matrix by.
 * @exception std::invalid_argument Thrown if the matrices have different
 * dimensions.
 */
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Matrix dimensions are not suitable for multiplication.");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(result);
}

namespace {
/**
 * @brief Calculates the minor of a matrix.
 *
 * A minor is a sub-matrix of a matrix, obtained by deleting one row and one
 * column from the matrix. The minor is used in calculating the determinant of
 * a matrix.
 *
 * @param m The matrix to calculate the minor of.
 * @param skip_row The row to skip in the minor.
 * @param skip_col The column to skip in the minor.
 * @return The minor of the matrix.
 */
S21Matrix GetMinor(const S21Matrix& m, int skip_row, int skip_col) {
  S21Matrix minor(m.get_rows() - 1, m.get_cols() - 1);
  int r_m = 0;
  for (int i = 0; i < m.get_rows(); ++i) {
    if (i == skip_row) continue;
    int c_m = 0;
    for (int j = 0; j < m.get_cols(); ++j) {
      if (j == skip_col) continue;
      minor(r_m, c_m) = m(i, j);
      c_m++;
    }
    r_m++;
  }
  return minor;
}
}  // namespace

/**
 * @brief Calculates the transpose of a matrix.
 *
 * The transpose of a matrix is a matrix with the elements of the rows of the
 * original matrix as the columns of the new matrix.
 *
 * @return The transpose of the matrix.
 */
S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result(j, i) = matrix_[i][j];
    }
  }
  return result;
}

/**
 * @brief Calculates the determinant of the matrix.
 *
 * The determinant of a matrix is a scalar value that can be used to determine
 * the solvability of a system of linear equations. The determinant of a matrix
 * can be calculated using the following formula:
 *
 *  det(A) = a11 * [a22*a33 - a23*a32] - a12 * [a21*a33 - a23*a31] +
 *  a13 * [a21*a32 - a22*a31]
 *
 * This function calculates the determinant of the matrix using the recursive
 * formula above.
 *
 * @exception std::invalid_argument Thrown if the matrix is not square.
 * @return The determinant of the matrix.
 */
double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Determinant can only be calculated for a square matrix.");
  }

  double result = 0.0;

  if (rows_ == 1) return matrix_[0][0];
  if (rows_ == 2)
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];

  for (int i = 0; i < cols_; ++i) {
    S21Matrix minor = GetMinor(*this, 0, i);
    double minor_det = minor.Determinant();
    double sign = (i % 2 == 0) ? 1.0 : -1.0;
    result += sign * matrix_[0][i] * minor_det;
  }

  return result;
}

/**
 * @brief Calculates the matrix of algebraic complements.
 *
 * The matrix of algebraic complements is a matrix containing the algebraic
 * complements of all elements of the matrix. The algebraic complement of an
 * element is the determinant of the minor of that element, multiplied by -1 to
 * the power of the sum of the row and column indices of the element.
 *
 * @return The matrix of algebraic complements.
 * @exception std::invalid_argument Thrown if the matrix is not square.
 */
S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Complements can only be calculated for a square matrix.");
  }
  S21Matrix result(rows_, cols_);

  if (rows_ == 1) {
    result(0, 0) = 1;
    return result;
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix minor = GetMinor(*this, i, j);
      double minor_det = minor.Determinant();
      double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
      result(i, j) = sign * minor_det;
    }
  }
  return result;
}

/**
 * @brief Calculates the inverse matrix.
 *
 * The inverse matrix is the matrix that, when multiplied by the original
 * matrix, results in the identity matrix. The inverse matrix is calculated
 * using the formula A^-1 = 1/|A| \* adj(A), where adj(A) is the adjugate of A,
 * and |A| is the determinant of A.
 *
 * @return The inverse matrix.
 * @exception std::invalid_argument Thrown if the matrix is singular (i.e. its
 * determinant is zero).
 */
S21Matrix S21Matrix::InverseMatrix() const {
  double det = Determinant();
  if (std::fabs(det) < 1e-7) {
    throw std::invalid_argument(
        "Matrix is singular (determinant is zero), cannot find inverse.");
  }

  S21Matrix complements = CalcComplements();

  S21Matrix adjugate = complements.Transpose();

  adjugate.MulNumber(1.0 / det);

  return adjugate;
}
