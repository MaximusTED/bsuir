// Copyright (c) 2016, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 2.2.2: System of linear equations (Zeidel elimination).

// Методы простой итерации, Зейделя – по вариантам, МП4.
//
// Исходную матрицу А и вектор свободных b ввести с клавиатуры, записать в файл
// с названием, например, data.txt, считать значения массивов A и b из этого
// файла.  Вычислить корни СЛАУ, т.е. найти вектор x, сохранить этот вектор в
// файле с названием result.txt.
//
// Вычислить невязку (2.1).
//
// |q   1   0   0   0|   | x1 |   | 0 |
// |1  -2   1   0   0|   | x2 |   | d |
// |0   1  -2   1   0| x | x3 | = | d |
// |0   0   1  -2   1|   | x4 |   | d |
// |0   0   0   1   q|   | x5 |   | 0 |
//
// q = -2.57, d = 2, e = 10^-4

#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>

#include "../matrix_solvers.h"
#include "../null_streams.h"

namespace {

template <typename T>
int run_main() {
  std_extensions::nullostream null_cout;

  std::size_t n;
  std::vector<std::vector<T>> matrix;
  std::vector<T> b;
  int result_code;

  T e;

  // Читаем с клавиатуры.
  std::tie(matrix, b, n, result_code) =
      linear_equations::in_matrixes(std::cin, std::cout, &e);
  if (result_code != EXIT_SUCCESS) return result_code;

  // Пишем в файл данные.
  std::ofstream out_data_file("data.txt");
  if (!out_data_file) return EXIT_FAILURE;

  if (!linear_equations::out_matrixes(out_data_file, matrix, b, &e)) {
    return EXIT_FAILURE;
  }

  // Читаем из файла.
  std::ifstream in_data_file("data.txt");
  if (!in_data_file) return EXIT_FAILURE;

  std::tie(matrix, b, n, result_code) =
      linear_equations::in_matrixes(in_data_file, null_cout, &e);
  if (result_code != EXIT_SUCCESS) return result_code;

  std::size_t k{0};
  const T w = 1;

  // Считаем по Зейделю.
  const std::vector<T> x =
      linear_equations::evaluate_by_zeidel(matrix, b, e, w, &k);

  // Считаем невязку.
  const T residual = linear_equations::evaluate_residual(matrix, b, x);

  // Пишем в файл результаты.
  std::ofstream out_result_file("result.txt");
  if (!out_result_file) return EXIT_FAILURE;

  linear_equations::out_roots(out_result_file, x, &residual, &w, &k);

  return 0;
}

}  // namespace

int main() { return run_main<double>(); }
