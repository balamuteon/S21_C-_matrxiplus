#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

// --- Тестирование get_rows() и get_cols() ---
TEST(AccessorsSuite, Getters) {
  // Arrange
  S21Matrix m1;  // 3x3 по умолчанию
  S21Matrix m2(5, 10);

  // Assert
  ASSERT_EQ(m1.get_rows(), 3);
  ASSERT_EQ(m1.get_cols(), 3);

  ASSERT_EQ(m2.get_rows(), 5);
  ASSERT_EQ(m2.get_cols(), 10);
}

// --- Тестирование set_rows() ---
TEST(MutatorsSuite, SetRowsIncrease) {
  // Arrange
  S21Matrix m(2, 2);
  m(1, 1) = 99.0;

  // Act
  m.set_rows(4);

  // Assert
  ASSERT_EQ(m.get_rows(), 4);
  ASSERT_EQ(m.get_cols(), 2);
  // Проверяем, что старые данные сохранились
  ASSERT_DOUBLE_EQ(m(1, 1), 99.0);
  // Проверяем, что новые элементы - нули
  ASSERT_DOUBLE_EQ(m(3, 1), 0.0);
}

TEST(MutatorsSuite, SetRowsDecrease) {
  // Arrange
  S21Matrix m(4, 2);
  m(0, 1) = 88.0;
  m(1, 1) = 99.0;

  // Act
  m.set_rows(2);

  // Assert
  ASSERT_EQ(m.get_rows(), 2);
  ASSERT_EQ(m.get_cols(), 2);
  // Проверяем, что сохранились только те данные, что поместились
  ASSERT_DOUBLE_EQ(m(0, 1), 88.0);
}

TEST(MutatorsSuite, SetRowsThrows) {
  // Arrange
  S21Matrix m(2, 2);

  // Assert
  ASSERT_THROW(m.set_rows(0), std::invalid_argument);
  ASSERT_THROW(m.set_rows(-5), std::invalid_argument);
}

// --- Тестирование set_cols() ---
TEST(MutatorsSuite, SetColsIncrease) {
  // Arrange
  S21Matrix m(2, 2);
  m(1, 1) = 99.0;

  // Act
  m.set_cols(4);

  // Assert
  ASSERT_EQ(m.get_rows(), 2);
  ASSERT_EQ(m.get_cols(), 4);
  // Проверяем, что старые данные сохранились
  ASSERT_DOUBLE_EQ(m(1, 1), 99.0);
  // Проверяем, что новые элементы - нули
  ASSERT_DOUBLE_EQ(m(1, 3), 0.0);
}

TEST(MutatorsSuite, SetColsDecrease) {
  // Arrange
  S21Matrix m(2, 4);
  m(1, 0) = 88.0;
  m(1, 1) = 99.0;

  // Act
  m.set_cols(2);

  // Assert
  ASSERT_EQ(m.get_rows(), 2);
  ASSERT_EQ(m.get_cols(), 2);
  // Проверяем, что сохранились только те данные, что поместились
  ASSERT_DOUBLE_EQ(m(1, 0), 88.0);
}

TEST(MutatorsSuite, SetColsThrows) {
  // Arrange
  S21Matrix m(2, 2);

  // Assert
  ASSERT_THROW(m.set_cols(0), std::invalid_argument);
  ASSERT_THROW(m.set_cols(-5), std::invalid_argument);
}