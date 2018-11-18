// Copyright (c) 2016, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 2.3: POL functions approximation.

#include <cmath>
#include <cstddef>
#include <cstdlib>  // For EXIT_*.
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using f64 = double;
using usize = std::size_t;
template <typename T>
using vec = std::vector<T, std::allocator<T>>;

// a = -1, b = 4, m = 5, n = 5. POL

struct point {
  explicit point(f64 the_x = 0, f64 the_y = 0) noexcept : x{the_x}, y{the_y} {}

  f64 x, y;
};

using function_values_table = vec<point>;

f64 f(f64 x) noexcept { return x * x + 5 * std::cos(x); }

vec<f64> POL(const function_values_table& source_points_table, usize n) {
  auto a = vec<vec<f64>>(n);
  for (auto& row : a) {
    row = vec<f64>(n);
  }
  auto c = vec<f64>(n);

  for (usize k{0}; k < n; ++k) {
    a[k][0] = 1;
    usize i = std::numeric_limits<usize>::max();

    for (usize m{1}; m < n; ++m) {
      ++i;

      if (i == k) {
        ++i;
      }

      const f64 d = source_points_table[k].x - source_points_table[i].x;
      a[k][m] = a[k][m - 1] / d;

      for (usize j{m - 1}; j >= 1; --j) {
        a[k][j] = (a[k][j - 1] - a[k][j] * source_points_table[i].x) / d;
      }

      a[k][0] *= -1 * source_points_table[i].x / d;
    }
  }

  for (usize i{0}; i < n; ++i) {
    f64 ci = 0;

    for (usize k{0}; k < n; ++k) {
      ci += a[k][i] * source_points_table[k].y;
    }

    c[i] = ci;
  }

  return c;
}

function_values_table POL(const function_values_table& source_points_table,
                          usize n, const vec<f64>& xes) {
  const auto c = POL(source_points_table, n);

  const auto k = xes.size();
  auto approximate_points_table = function_values_table(k);

  for (usize i{0}; i < k; ++i) {
    const f64 x = xes[i];
    f64 y = 0;

    for (usize j{0}; j < n; ++j) {
      y += c[j] * std::pow(x, j);
    }

    approximate_points_table[i] = point{x, y};
  }

  return approximate_points_table;
};

function_values_table create_source_table(int a, int b, usize m) {
  std::cout << std::setw(9) << "X"
            << "\t" << std::setw(9) << "Y" << std::endl;

  auto source_points_table = function_values_table(m);
  for (usize i{0}; i < m; ++i) {
    const f64 x = a + static_cast<f64>(i) * (b * 1.0 - a) / (m - 1.0);
    const f64 y = f(x);
    source_points_table[i] = point{x, y};

    std::cout << std::setw(9) << x << "\t" << std::setw(9) << y << std::endl;
  }

  return source_points_table;
}

vec<f64> create_approximation_table(int a, int b) {
  const usize k{21};

  auto xes = vec<f64>(k);
  for (usize j{0}; j < k; j++) {
    xes[j] = a + j * (b * 1.0 - a) / 20.0;
  }

  return xes;
}

void print_comparison_table(
    const function_values_table& approximated_points_table) {
  std::cout << std::endl;
  std::cout << std::setw(9) << "X"
            << "\t" << std::setw(9) << "Y"
            << "\t" << std::setw(9) << "Y'"
            << "\t" << std::setw(9) << "e" << std::endl;

  for (const auto& approximated_point : approximated_points_table) {
    const f64 x = approximated_point.x, y = f(x), ya = approximated_point.y,
              e = std::fabs(ya - y);

    std::cout << std::setw(9) << x << "\t" << std::setw(9) << y << "\t"
              << std::setw(9) << ya << "\t" << std::setw(9) << e << std::endl;
  }
}

int main() {
  int a, b;
  usize m, n;

  std::cout << "a = ";
  std::cin >> a;
  std::cout << "b = ";
  std::cin >> b;
  std::cout << "m = ";
  std::cin >> m;
  std::cout << "n = ";
  std::cin >> n;

  if (n > m) {
    std::cerr << "n should be less or equal m." << std::endl;
    return EXIT_FAILURE;
  }

  std::cout.flags(std::ios::right);
  std::cout.precision(4);  //-V112

  const function_values_table source_points_table =
      create_source_table(a, b, m);
  const vec<f64> xes = create_approximation_table(a, b);
  const function_values_table approximated_points_table =
      POL(source_points_table, n, xes);

  print_comparison_table(approximated_points_table);

  return EXIT_SUCCESS;
}
