#include "s21_matrix_oop.h"

// --- Constructors ---

/**
 * @brief Default constructor for S21Matrix.
 *
 * Initializes a 3x3 matrix with all elements set to zero.
 */
S21Matrix::S21Matrix() : rows_(3), cols_(3) { AllocateMatrix(); }

/**
 * @brief Parameterized constructor for S21Matrix.
 *
 * Initializes a matrix with the specified number of rows and columns.
 * Throws an exception if the provided dimensions are less than 1.
 *
 * @param rows Number of rows in the matrix.
 * @param cols Number of columns in the matrix.
 * @exception std::invalid_argument Thrown if rows or cols are less than 1.
 */
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("Incorrect matrix dimensions");
  }
  AllocateMatrix();
}

/**
 * @brief Copy constructor for S21Matrix.
 *
 * Creates a deep copy of the specified matrix.
 *
 * @param other The matrix to copy from.
 */
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  AllocateMatrix();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

/**
 * @brief Move constructor for S21Matrix.
 *
 * Creates a new matrix by transferring ownership of the memory from the
 * specified matrix. The original matrix is left in a valid but unspecified
 * state.
 *
 * @param other The matrix from which to transfer ownership.
 */
S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

/**
 * @brief Destructor for the S21Matrix class.
 *
 * This destructor deallocates the memory allocated for the matrix.
 * It iterates over each row to delete the allocated memory for columns
 * and then deletes the memory allocated for row pointers.
 * It ensures that no memory leaks occur by setting the matrix pointer
 * to nullptr after deallocation.
 */
S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
}