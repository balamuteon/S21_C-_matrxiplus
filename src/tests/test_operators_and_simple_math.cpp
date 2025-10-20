#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

// --- Тестирование операторов присваивания (=) ---
TEST(OperatorAssignment, CopyAssignment) {
  S21Matrix m1(2, 3);
  m1(1, 1) = 5.5;
  S21Matrix m2;

  m2 = m1;  // Копирующее присваивание

  ASSERT_EQ(m1.get_rows(), 2);
  ASSERT_EQ(m1.get_cols(), 3);
  ASSERT_EQ(m2.get_rows(), 2);
  ASSERT_EQ(m2.get_cols(), 3);
  ASSERT_DOUBLE_EQ(m1(1, 1), m2(1, 1));
}

TEST(OperatorAssignment, CopySelfAssignment) {
  S21Matrix m1(2, 3);
  m1(1, 1) = 5.5;

  m1 = m1;  // Самоприсваивание

  ASSERT_EQ(m1.get_rows(), 2);
  ASSERT_EQ(m1.get_cols(), 3);
  ASSERT_DOUBLE_EQ(m1(1, 1), 5.5);
}

TEST(OperatorAssignment, MoveAssignment) {
  S21Matrix m1(2, 3);
  m1(1, 1) = 5.5;
  S21Matrix m2;

  m2 = std::move(m1);  // Перемещающее присваивание

  ASSERT_EQ(m2.get_rows(), 2);
  ASSERT_EQ(m2.get_cols(), 3);
  ASSERT_DOUBLE_EQ(m2(1, 1), 5.5);
  ASSERT_EQ(m1.get_rows(), 0);
  ASSERT_EQ(m1.get_cols(), 0);
}

// --- Тестирование операторов доступа и сравнения ---
TEST(OperatorAccess, IndexOperator) {
  S21Matrix m(2, 2);
  m(1, 1) = 123.45;
  ASSERT_DOUBLE_EQ(m(1, 1), 123.45);
}

TEST(OperatorAccess, IndexOperatorConst) {
  const S21Matrix m(2, 2);
  // m(1, 1) = 123.45; // Эта строка не скомпилируется, что правильно
  ASSERT_DOUBLE_EQ(m(1, 1), 0.0);
}

TEST(OperatorAccess, IndexOperatorThrows) {
  S21Matrix m(2, 2);
  const S21Matrix& const_m = m;
  ASSERT_THROW(m(2, 0), std::out_of_range);
  ASSERT_THROW(const_m(0, 2), std::out_of_range);
}

TEST(OperatorComparison, Equality) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  S21Matrix m3(2, 2);
  m3(1, 1) = 1.0;
  S21Matrix m4(3, 2);

  ASSERT_TRUE(m1 == m2);
  ASSERT_FALSE(m1 == m3);
  ASSERT_FALSE(m1 == m4);
}

// --- Тестирование арифметических операторов ---
TEST(OperatorArithmetic, Plus) {
  S21Matrix m1(2, 2), m2(2, 2), expected(2, 2);
  m1(0, 0) = 1;
  m2(0, 0) = 5;
  expected(0, 0) = 6;

  S21Matrix result = m1 + m2;
  ASSERT_TRUE(result == expected);
}

TEST(OperatorArithmetic, PlusThrows) {
  S21Matrix m1(2, 2), m2(3, 2);
  ASSERT_THROW(m1 + m2, std::invalid_argument);
}

TEST(OperatorArithmetic, Minus) {
  S21Matrix m1(2, 2), m2(2, 2), expected(2, 2);
  m1(0, 0) = 10;
  m2(0, 0) = 3;
  expected(0, 0) = 7;

  S21Matrix result = m1 - m2;
  ASSERT_TRUE(result == expected);
}

TEST(OperatorArithmetic, MultiplyMatrix) {
  S21Matrix m1(2, 2), m2(2, 2), expected(2, 2);
  m1(0, 0) = 2;
  m1(0, 1) = 2;
  m2(0, 0) = 3;
  m2(1, 0) = 1;
  expected(0, 0) = 8;  // 2*3 + 2*1 = 8

  S21Matrix result = m1 * m2;
  ASSERT_TRUE(result == expected);
}

TEST(OperatorArithmetic, MultiplyNumber) {
  S21Matrix m1(2, 2), expected(2, 2);
  m1(1, 1) = 5;
  expected(1, 1) = 15;

  S21Matrix result = m1 * 3.0;
  ASSERT_TRUE(result == expected);
}

// --- Тестирование составных операторов присваивания ---
TEST(OperatorCompound, PlusAssignment) {
  S21Matrix m1(2, 2), m2(2, 2), expected(2, 2);
  m1(0, 0) = 1;
  m2(0, 0) = 5;
  expected(0, 0) = 6;

  m1 += m2;
  ASSERT_TRUE(m1 == expected);
}

TEST(OperatorCompound, MinusAssignment) {
  S21Matrix m1(2, 2), m2(2, 2), expected(2, 2);
  m1(0, 0) = 10;
  m2(0, 0) = 3;
  expected(0, 0) = 7;

  m1 -= m2;
  ASSERT_TRUE(m1 == expected);
}

TEST(OperatorCompound, MultiplyAssignmentMatrix) {
  S21Matrix m1(2, 2), m2(2, 2), expected(2, 2);
  m1(0, 0) = 2;
  m1(0, 1) = 2;
  m2(0, 0) = 3;
  m2(1, 0) = 1;
  expected(0, 0) = 8;

  m1 *= m2;
  ASSERT_TRUE(m1 == expected);
}

TEST(OperatorCompound, MultiplyAssignmentNumber) {
  S21Matrix m1(2, 2), expected(2, 2);
  m1(1, 1) = 5;
  expected(1, 1) = 15;

  m1 *= 3.0;
  ASSERT_TRUE(m1 == expected);
}