// Copyright (c) 2016, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.

#ifndef MATRIX_SOLVERS_H_
#define MATRIX_SOLVERS_H_

#include <cassert>   // assert
#include <cmath>     // std::fabs
#include <cstdlib>   // usize, EXIT_*
#include <iomanip>   // std::setw
#include <iostream>  // std::basic_istream, std::basic_ostream
#include <limits>    // std::numeric_limits
#include <tuple>     // std::tuple
#include <vector>    // vec

namespace linear_equations {

template <typename T>
using vec = std::vector<T, std::allocator<T>>;

using usize = std::size_t;

using i32 = int;

// Basic input stream root.
using istream = std::basic_istream<char, std::char_traits<char>>;

// Basic output stream root.
using ostream = std::basic_ostream<char, std::char_traits<char>>;

// Read source matrix and free members.
template <typename T>
std::tuple<vec<vec<T>>, vec<T>, usize, i32> in_matrixes(istream &istream,
                                                        ostream &ostream,
                                                        T *e = nullptr) {
  ostream << "Poryadok: ";

  usize n;
  if (!(istream >> n)) {
    return make_tuple(vec<vec<T>>(), vec<T>(), 0, EXIT_FAILURE);
  }

  if (e) {
    ostream << "Tochnost: ";

    if (!(istream >> *e)) {
      return make_tuple(vec<vec<T>>(), vec<T>(), 0, EXIT_FAILURE);
    }
  }

  auto b = vec<T>(n);
  auto matrix = vec<vec<T>>(n);
  for (auto &row : matrix) {
    row.resize(n);
  }

  ostream << "Vvedite koefficienty i svobodnye chleny: " << std::endl;

  for (usize i = 0; i < n; i++) {
    for (usize j = 0; j < n; j++) {
      ostream << "a[" << i + 1 << ", " << j + 1 << "] = ";

      if (!(istream >> matrix[i][j])) {
        return make_tuple(vec<vec<T>>(), vec<T>(), 0, EXIT_FAILURE);
      }
    }

    ostream << "b[" << i + 1 << "] = ";

    if (!(istream >> b[i])) {
      return make_tuple(vec<vec<T>>(), vec<T>(), 0, EXIT_FAILURE);
    }
  }

  return std::make_tuple(matrix, b, n, EXIT_SUCCESS);
}

// Write matrixes to stream.
template <typename T>
bool out_matrixes(ostream &ostream, const vec<vec<T>> &matrix, const vec<T> &b,
                  const T *const e = nullptr) {
  const usize n = b.size();
  assert(n == matrix.size());  // matrix is square with side n.

  bool is_success = (ostream << n << std::endl).good();

  if (is_success && e) {
    is_success = (ostream << *e << std::endl).good();
  }

  if (is_success) {
    usize i = 0;

    for (const auto &row : matrix) {
      assert(n == row.size());  // matrix is square with side n.

      for (const auto item : row) {
        is_success = (ostream << std::setw(8) << item).good();

        if (!is_success) return false;
      }

      is_success =
          (ostream << "\t" << std::setw(8) << b[i++] << std::endl).good();

      if (!is_success) return false;
    }
  }

  return is_success;
}

// Evaluate LES by Gauss.
template <typename T>
vec<T> evaluate_by_gauss(vec<vec<T>> &matrix, vec<T> &b) {
  const usize n = b.size();
  assert(n == matrix.size());  // matrix is square with side n.

  // Triangle with zeros down the main diagonal.
  for (usize k = 0; k < n; k++) {
    assert(n == matrix[k].size());  // matrix is square with side n.

    for (usize j = k + 1; j < n; j++) {
      const T d = matrix[j][k] / matrix[k][k];

      for (usize i = k; i < n; i++) {
        matrix[j][i] -= d * matrix[k][i];
      }

      b[j] -= d * b[k];
    }
  }

  vec<T> x = vec<T>(n);

  // Reverse.
  for (std::ptrdiff_t k = n - 1; k >= 0; k--) {
    T d{};

    for (usize j = k + 1; j < n; j++) {
      const T s = matrix[k][j] * x[j];
      d += s;
    }

    x[k] = (b[k] - d) / matrix[k][k];
  }

  return x;
}

// Evaluate LES by Zeidel.
template <typename T>
vec<T> evaluate_by_zeidel(const vec<vec<T>> &matrix, const vec<T> &b, const T e,
                          const T w, usize *k) {
  const usize n = b.size();
  assert(n == matrix.size());  // matrix is square with side n.

  vec<T> x = vec<T>(n, 1);
  vec<T> x0 = vec<T>(n, 1);

  constexpr usize max_k = 1000;
  T de;
  *k = {};

  // For checking index range in cycles further.
  assert(n <= static_cast<usize>(std::numeric_limits<std::ptrdiff_t>::max()));

  do {
    de = {};

    for (std::ptrdiff_t i = 0; i < static_cast<ptrdiff_t>(n); i++) {
      assert(n == matrix[i].size());  // matrix is square with side n.

      T s = b[i];

      for (std::ptrdiff_t j = 0; j <= i - 1; j++) {
        s -= matrix[i][j] * x0[j];
      }

      for (usize j = i + 1; j < n; j++) {
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
template <typename T>
T evaluate_residual(const vec<vec<T>> &matrix, const vec<T> &b,
                    const vec<T> &x) {
  const usize n = b.size();
  assert(n == matrix.size());  // matrix is square with side n.
  assert(n == x.size());       // vector with size n.

  T residual = {};
  for (usize i = 0; i < n; i++) {
    T s = {};

    for (usize j = 0; j < n; j++) {
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
template <typename T>
void out_roots(ostream &ostream, const vec<T> &x,
               const T *const residual = nullptr, const T *const w = nullptr,
               const usize *const k = nullptr) {
  if (residual) ostream << "Nevjazka: " << *residual << std::endl;
  if (k && w) ostream << *k << " iteracij dla relaksacii " << *w << std::endl;

  const usize n = x.size();
  for (usize i = 0; i < n; i++)
    ostream << "x[" << i + 1 << "] = " << x[i] << " " << std::endl;
}

}  // namespace linear_equations

#endif  // !MATRIX_SOLVERS_H_
