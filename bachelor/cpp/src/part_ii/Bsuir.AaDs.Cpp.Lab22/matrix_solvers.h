// Copyright (c) 2016, reginell. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MATRIX_SOLVERS_H_
#define MATRIX_SOLVERS_H_

#include <cstdlib>   // std::size_t, EXIT_*
#include <cassert>   // assert
#include <cmath>     // std::fabs
#include <iostream>  // std::basic_istream, std::basic_ostream 
#include <iomanip>   // std::setw
#include <limits>    // std::numeric_limits
#include <tuple>     // std::tuple
#include <vector>    // std::vector

namespace linear_equations {

// Basic input stream root.
using istream = std::basic_istream<char, std::char_traits<char>>;

// Basic output stream root.
using ostream = std::basic_ostream<char, std::char_traits<char>>;

// Read source matrix and free members.
template<typename T>
std::tuple<std::vector<std::vector<T>>,
           std::vector<T>,
           std::size_t,
           int> in_matrixes(istream &istream,
                            ostream &ostream,
                            T *e = nullptr) {
  ostream << "Poryadok: ";

  std::size_t n;
  if (!(istream >> n)) {
    return make_tuple(std::vector<std::vector<T>>(),
                      std::vector<T>(),
                      0,
                      EXIT_FAILURE);
  }

  if (e) {
    ostream << "Tochnost: ";
    
    if (!(istream >> *e)) {
      return make_tuple(std::vector<std::vector<T>>(),
                        std::vector<T>(),
                        0,
                        EXIT_FAILURE);
    }
  }

  auto b = std::vector<T>(n);
  auto matrix = std::vector<std::vector<T>>(n);
  for (auto &row : matrix) {
    row.resize(n);
  }

  ostream << "Vvedite koefficienty i svobodnye chleny: " << std::endl;

  for (std::size_t i = 0; i < n; i++) {
    for (std::size_t j = 0; j < n; j++) {
      ostream << "a[" << i + 1 << ", " << j + 1 << "] = ";

      if (!(istream >> matrix[i][j])) {
        return make_tuple(std::vector<std::vector<T>>(),
                          std::vector<T>(),
                          0,
                          EXIT_FAILURE);
      }
    }

    ostream << "b[" << i + 1 << "] = ";
    
    if (!(istream >> b[i])) {
      return make_tuple(std::vector<std::vector<T>>(),
                        std::vector<T>(),
                        0,
                        EXIT_FAILURE);
    }
  }

  return std::make_tuple(matrix, b, n, EXIT_SUCCESS);
}

// Write matrixes to stream.
template<typename T>
void out_matrixes(ostream &ostream,
                  const std::vector<std::vector<T>> &matrix,
                  const std::vector<T>& b,
                  const T * const e = nullptr) {
  const std::size_t n = b.size();
  assert(n == matrix.size());   // matrix is square with side n.

  ostream << n << std::endl;
  if (e) ostream << *e << std::endl;

  std::size_t i = 0;

  for (const auto &row : matrix) {
    assert(n == row.size());   // matrix is square with side n.

    for (const auto item : row) {
      ostream << std::setw(8) << item;
    }

    ostream << "\t" << std::setw(8) << b[i++] << std::endl;
  }
}

// Evaluate LES by Gauss.
template<typename T>
std::vector<T> evaluate_by_gauss(std::vector<std::vector<T>> &matrix,
                                 std::vector<T>& b) {
  const std::size_t n = b.size();
  assert(n == matrix.size());   // matrix is square with side n.

  // Triangle with zeros down the main diagonal.
  for (std::size_t k = 0; k < n; k++) {
    assert(n == matrix[k].size());   // matrix is square with side n.

    for (std::size_t j = k + 1; j < n; j++) {
      const T d = matrix[j][k] / matrix[k][k];

      for (std::size_t i = k; i < n; i++) {
        matrix[j][i] -= d * matrix[k][i];
      }

      b[j] -= d * b[k];
    }
  }

  std::vector<T> x = std::vector<T>(n);

  // Reverse.
  for (std::ptrdiff_t k = n - 1; k >= 0; k--) {
    T d{};

    for (std::size_t j = k + 1; j < n; j++) {
      const T s = matrix[k][j] * x[j];
      d += s;
    }

    x[k] = (b[k] - d) / matrix[k][k];
  }

  return x;
}

// Evaluate LES by Zeidel.
template<typename T>
std::vector<T> evaluate_by_zeidel(const std::vector<std::vector<T>> &matrix,
                                  const std::vector<T>& b,
                                  const T e,
                                  const T w,
                                  std::size_t *k) {
  const std::size_t n = b.size();
  assert(n == matrix.size());   // matrix is square with side n.

  std::vector<T> x = std::vector<T>(n, 1);
  std::vector<T> x0 = std::vector<T>(n, 1);

  constexpr std::size_t max_k = 1000;
  T de;
  *k = {};

  // For checking index range in cycles further.
  assert(n <= static_cast<std::size_t>(
    std::numeric_limits<std::ptrdiff_t>::max()));

  do {
    de = {};

    for (std::ptrdiff_t i = 0; i < static_cast<ptrdiff_t>(n); i++) {
      assert(n == matrix[i].size());   // matrix is square with side n.

      T s = b[i];

      for (std::ptrdiff_t j = 0; j <= i - 1; j++) {
        s -= matrix[i][j] * x0[j];
      }

      for (std::size_t j = i + 1; j < n; j++) {
        s -= matrix[i][j] * x0[j];
      }

      s /= matrix[i][i];
      s = w * s + (1 - w) * x[i];

      const T d = fabs(x[i] - s);
      if (d > de) de = d;

      x[i] = s;
    }

    ++(*k);

    for (std::ptrdiff_t i = 0; i < static_cast<ptrdiff_t>(n); i++) {
      x0[i] = x[i];
    }
  } while (*k < max_k && de >= e);

  return x;
}

// Evaluate residual.
template<typename T>
T evaluate_residual(const std::vector<std::vector<T>> &matrix,
                    const std::vector<T>& b,
                    const std::vector<T>& x) {
  const std::size_t n = b.size();
  assert(n == matrix.size());   // matrix is square with side n.
  assert(n == x.size());        // vector with size n.

  T residual = {};
  for (std::size_t i = 0; i < n; i++) {
    T s = {};

    for (std::size_t j = 0; j < n; j++) {
      s += matrix[i][j] * x[j];
    }

    const T new_residual = std::fabs(b[i] - s);
    if (new_residual > residual) {
      residual = new_residual;
    }
  }

  return residual;
}

// Write roots to stream.
template<typename T>
void out_roots(ostream& ostream,
               const std::vector<T>& x,
               const T * const residual = nullptr,
               const T * const w = nullptr,
               const std::size_t * const k = nullptr) {
  if (residual) ostream << "Nevjazka: " << *residual << std::endl;
  if (k && w) ostream << *k << " iteracij dla relaksacii " << *w << std::endl;

  const std::size_t n = x.size();
  for (std::size_t i = 0; i < n; i++)
    ostream << "x[" << i + 1 << "] = " << x[i] << " " << std::endl;
}

}  // namespace linear_equations

#endif // !MATRIX_SOLVERS_H_
