// Copyright (c) 2016, reginell. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 2_2_1: System of linear equations (Gaussian elimination).

// Метод Гаусса, всем один – данные по вариантам, МП4.
//
// Исходную матрицу А и вектор свободных b ввести с клавиатуры, записать в файл
// с названием, например, data.txt, считать значения массивов A и b из этого
// файла.  Вычислить корни СЛАУ, т.е. найти вектор x, сохранить этот вектор в
// файле с названием result.txt.
//
// |q   1   0   0   0|   | x1 |   | 0 |
// |1  -2   1   0   0|   | x2 |   | d |
// |0   1  -2   1   0| x | x3 | = | d |
// |0   0   1  -2   1|   | x4 |   | d |
// |0   0   0   1   q|   | x5 |   | 0 |
//
// q = -2.57, d = 2

#include <cstdlib>   // std::size_t, EXIT_*
#include <iostream>
#include <fstream>
#include <vector>    // std::vector
#include <tuple>     // std::tuple

#include "../matrix_solvers.h"
#include "../null_streams.h"

namespace {

using namespace linear_equations;

template<typename T>
int run_main() {
  using namespace linear_equations;

  std_extensions::nullostream null_cout;

  std::size_t n;
  std::vector<std::vector<T>> matrix;
  std::vector<T> b;
  int result_code;

  // Читаем с клавиатуры.
  std::tie(matrix, b, n, result_code) = in_matrixes<T>(std::cin, std::cout);
  if (result_code != EXIT_SUCCESS) return result_code;

  // Пишем в файл данные.
  std::ofstream out_data_file("data.txt");
  if (!out_data_file) return EXIT_FAILURE;

  out_matrixes(out_data_file, matrix, b);

  // Читаем с файла.
  std::ifstream in_data_file("data.txt");
  if (!in_data_file) return EXIT_FAILURE;

  std::tie(matrix, b, n, result_code) = in_matrixes<T>(in_data_file, null_cout);
  if (result_code != EXIT_SUCCESS) return result_code;

  // Считаем по Гауссу.
  std::vector<T> x = evaluate_by_gauss(matrix, b);

  // Пишем в файл результаты.
  std::ofstream out_result_file("result.txt");
  if (!out_result_file) return EXIT_FAILURE;

  out_roots(out_data_file, x);

  return EXIT_SUCCESS;
}

}  // namespace

int main() {
  return run_main<double>();
}
