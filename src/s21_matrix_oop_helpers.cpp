#include "s21_matrix_oop.h"

// --- Accessors ---

/**
 * @brief Get the number of rows in the matrix.
 *
 * @return Number of rows.
 */
int S21Matrix::get_rows() const { return rows_; }

/**
 * @brief Get the number of columns in the matrix.
 *
 * @return Number of columns.
 */
int S21Matrix::get_cols() const { return cols_; }

// --- Mutators ---

/**
 * @brief Set the number of rows for the matrix. If the number of rows
 * increases, the new rows are initialized to zero. Throws an exception if the
 * input is less than 1.
 *
 * @param new_rows The new number of rows.
 */
void S21Matrix::set_rows(int new_rows) {
  if (new_rows < 1) {
    throw std::invalid_argument("Number of rows must be at least 1.");
  }
  if (new_rows == rows_) return;

  S21Matrix new_matrix(new_rows, cols_);

  int rows_to_copy = std::min(rows_, new_rows);
  for (int i = 0; i < rows_to_copy; ++i) {
    for (int j = 0; j < cols_; ++j) {
      new_matrix.matrix_[i][j] = matrix_[i][j];
    }
  }

  *this = std::move(new_matrix);
}

/**
 * @brief Set the number of columns for the matrix. If the number of columns
 * increases, the new columns are initialized to zero. Throws an exception if
 * the input is less than 1.
 *
 * @param new_cols The new number of columns.
 */
void S21Matrix::set_cols(int new_cols) {
  if (new_cols < 1) {
    throw std::invalid_argument("Number of columns must be at least 1.");
  }
  if (new_cols == cols_) return;

  S21Matrix new_matrix(rows_, new_cols);

  int cols_to_copy = std::min(cols_, new_cols);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_to_copy; ++j) {
      new_matrix.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = std::move(new_matrix);
}

// --- Allocators ---

/**
 * @brief Allocate memory for the matrix with the current number of rows and
 * columns. Initializes all elements to zero.
 */
void S21Matrix::AllocateMatrix() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

// --- Printers ---

/**
 * @brief Print the matrix to the standard output with one decimal precision.
 */
// void S21Matrix::printMatrix() const {
//   for (int i = 0; i < rows_; i++) {
//     for (int j = 0; j < cols_; j++) printf("%.1lf ", matrix_[i][j]);
//     printf("\n");
//   }
// }
