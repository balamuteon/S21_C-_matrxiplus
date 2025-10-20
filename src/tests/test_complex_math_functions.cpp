#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

// --- Тестирование Transpose ---
TEST(MathOperations, Transpose) {
  // Arrange
  S21Matrix m1(2, 3);
  m1(1, 2) = 5.5;

  // Act
  S21Matrix result = m1.Transpose();

  // Assert
  ASSERT_EQ(result.get_rows(), 3);
  ASSERT_EQ(result.get_cols(), 2);
  ASSERT_DOUBLE_EQ(result(2, 1), 5.5);
}

// --- Тестирование Determinant ---
TEST(MathOperations, DeterminantBasic) {
  S21Matrix m(2, 2);
  // 1*4 - 2*3 = 4 - 6 = -2
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;
  ASSERT_DOUBLE_EQ(m.Determinant(), -2.0);
}

TEST(MathOperations, DeterminantComplex) {
  S21Matrix m(3, 3);
  m(0, 0) = 2;
  m(0, 1) = 5;
  m(0, 2) = 7;
  m(1, 0) = 6;
  m(1, 1) = 3;
  m(1, 2) = 4;
  m(2, 0) = 5;
  m(2, 1) = -2;
  m(2, 2) = -3;
  ASSERT_DOUBLE_EQ(m.Determinant(), -1.0);
}

TEST(MathOperations, DeterminantThrows) {
  S21Matrix m(2, 3);  // Не квадратная
  ASSERT_THROW(m.Determinant(), std::invalid_argument);
}

// --- Тестирование CalcComplements ---
TEST(MathOperations, CalcComplements) {
  S21Matrix m(3, 3);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;
  m(1, 0) = 0;
  m(1, 1) = 4;
  m(1, 2) = 5;
  m(2, 0) = 1;
  m(2, 1) = 0;
  m(2, 2) = 6;

  S21Matrix expected(3, 3);
  expected(0, 0) = 24;
  expected(0, 1) = 5;
  expected(0, 2) = -4;
  expected(1, 0) = -12;
  expected(1, 1) = 3;
  expected(1, 2) = 2;
  expected(2, 0) = -2;
  expected(2, 1) = -5;
  expected(2, 2) = 4;

  S21Matrix result = m.CalcComplements();
  ASSERT_TRUE(result == expected);
}

TEST(MathOperations, CalcComplementsThrows) {
  S21Matrix m(2, 3);  // Не квадратная
  ASSERT_THROW(m.CalcComplements(), std::invalid_argument);
}

// --- Тестирование InverseMatrix ---
TEST(MathOperations, InverseMatrix) {
  S21Matrix m(3, 3);
  m(0, 0) = 2;
  m(0, 1) = 5;
  m(0, 2) = 7;
  m(1, 0) = 6;
  m(1, 1) = 3;
  m(1, 2) = 4;
  m(2, 0) = 5;
  m(2, 1) = -2;
  m(2, 2) = -3;

  S21Matrix expected(3, 3);
  expected(0, 0) = 1;
  expected(0, 1) = -1;
  expected(0, 2) = 1;
  expected(1, 0) = -38;
  expected(1, 1) = 41;
  expected(1, 2) = -34;
  expected(2, 0) = 27;
  expected(2, 1) = -29;
  expected(2, 2) = 24;

  S21Matrix result = m.InverseMatrix();
  ASSERT_TRUE(result == expected);
}

TEST(MathOperations, InverseMatrixThrows) {
  S21Matrix m(2, 2);
  // Определитель = 1*4 - 2*2 = 0
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 2;
  m(1, 1) = 4;
  ASSERT_THROW(m.InverseMatrix(), std::invalid_argument);
}
// --- Покрытие выброса исключений в SubMatrix и MulMatrix ---

TEST(EdgeCases, SubMatrixThrows) {
  // Arrange
  S21Matrix m1(2, 3);
  S21Matrix m2(3, 2);  // Матрицы разного размера

  // Act & Assert
  // Этот тест покрывает ветку с throw в методе SubMatrix
  ASSERT_THROW(m1.SubMatrix(m2), std::invalid_argument);
}

TEST(EdgeCases, MulMatrixThrows) {
  // Arrange
  S21Matrix m1(2, 3);
  S21Matrix m2(4, 2);  // Несовместимые размеры для умножения (3 != 4)

  // Act & Assert
  // Этот тест покрывает ветку с throw в методе MulMatrix
  ASSERT_THROW(m1.MulMatrix(m2), std::invalid_argument);
}

// --- Покрытие граничных случаев для матриц 1x1 ---

TEST(EdgeCases, Determinant_1x1_Matrix) {
  // Arrange
  S21Matrix m(1, 1);
  m(0, 0) = 15.5;

  // Act & Assert
  // Этот тест покрывает ветку 'if (rows_ == 1)' в методе Determinant
  ASSERT_DOUBLE_EQ(m.Determinant(), 15.5);
}

TEST(EdgeCases, CalcComplements_1x1_Matrix) {
  // Arrange
  S21Matrix m(1, 1);
  m(0, 0) = 15.5;

  S21Matrix expected(1, 1);
  expected(0, 0) = 1;  // По определению, для матрицы 1x1 алгебр. дополнение = 1

  // Act
  S21Matrix result = m.CalcComplements();

  // Assert
  // Этот тест покрывает ветку 'if (result->rows == 1 ...)' в CalcComplements
  ASSERT_TRUE(result == expected);
}