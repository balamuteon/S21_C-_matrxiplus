#include <gtest/gtest.h>

#include "s21_matrix_oop.h"  // Указываем путь к нашему заголовочному файлу

// --- Тестирование S21Matrix() ---
TEST(ConstructorSuite, DefaultConstructor) {
  // Arrange & Act
  S21Matrix m;

  // Assert
  ASSERT_EQ(m.get_rows(), 3);
  ASSERT_EQ(m.get_cols(), 3);
  // Проверим, что хотя бы один элемент действительно 0, т.к. конструктор должен
  // их обнулять
  ASSERT_DOUBLE_EQ(m(1, 1), 0.0);
}

// --- Тестирование S21Matrix(int, int) ---
TEST(ConstructorSuite, ParametrizedConstructor) {
  // Arrange & Act
  S21Matrix m(5, 10);

  // Assert
  ASSERT_EQ(m.get_rows(), 5);
  ASSERT_EQ(m.get_cols(), 10);
}

TEST(ConstructorSuite, ParametrizedConstructorThrows) {
  // Проверяем, что конструктор бросает исключение на некорректные данные
  ASSERT_THROW(S21Matrix m(0, 5), std::invalid_argument);
  ASSERT_THROW(S21Matrix m(5, 0), std::invalid_argument);
  ASSERT_THROW(S21Matrix m(-1, 5), std::invalid_argument);
}

// --- Тестирование S21Matrix(const S21Matrix&) ---
TEST(ConstructorSuite, CopyConstructor) {
  // Arrange
  S21Matrix m1(2, 2);
  m1(0, 1) = 55.5;
  m1(1, 0) = -10;

  // Act: Вызываем конструктор копирования
  S21Matrix m2 = m1;

  // Assert
  // 1. Проверяем, что размеры и данные скопировались
  ASSERT_EQ(m2.get_rows(), 2);
  ASSERT_EQ(m2.get_cols(), 2);
  ASSERT_DOUBLE_EQ(m2(0, 1), 55.5);

  // 2. Важнейшая проверка на ГЛУБОКОЕ копирование
  m2(0, 1) = 999;  // Меняем копию
  // Проверяем, что оригинал НЕ изменился
  ASSERT_DOUBLE_EQ(m1(0, 1), 55.5);
}

// --- Тестирование S21Matrix(S21Matrix&&) ---
TEST(ConstructorSuite, MoveConstructor) {
  // Arrange
  S21Matrix m1(4, 4);
  m1(3, 3) = 123.456;

  // Act: Вызываем конструктор перемещения
  S21Matrix m2 = std::move(m1);

  // Assert
  // 1. Проверяем, что m2 "украла" данные у m1
  ASSERT_EQ(m2.get_rows(), 4);
  ASSERT_EQ(m2.get_cols(), 4);
  ASSERT_DOUBLE_EQ(m2(3, 3), 123.456);

  // 2. Проверяем, что m1 осталась в пустом, но корректном состоянии
  ASSERT_EQ(m1.get_rows(), 0);
  ASSERT_EQ(m1.get_cols(), 0);
}

// --- Тестирование ~S21Matrix() ---
// Деструктор тестируется неявно. Если после выполнения всех этих тестов
// инструменты вроде Valgrind или sanitizers (ASan) не покажут утечек памяти,
// значит, деструктор работает правильно. Специальный тест для него не пишется.
// Сам факт, что программа с созданием и уничтожением объектов не падает,
// уже является хорошим тестом.