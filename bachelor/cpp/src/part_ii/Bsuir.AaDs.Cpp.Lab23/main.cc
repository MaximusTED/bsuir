// Copyright (c) 2016, reginell. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 2.3: POL functions approximation.

#include <cmath>
#include <cstddef>
#include <cstdlib>   // For EXIT_*.
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>

// a = -1, b = 4, m = 5, n = 5. POL

struct point {
  explicit point(double xi = 0, double yi = 0)
    : x{xi}, y{yi} {
  }

  double x, y;
};

using function_values_table = std::vector<point>;

double f(double x) {
  return x * x + 5 * std::cos(x);
}

std::vector<double> POL(const function_values_table& source_points_table,
                        std::size_t n) {
  auto a = std::vector<std::vector<double>>(n);
  for (auto &row : a) {
    row = std::vector<double>(n);
  }
  auto c = std::vector<double>(n);

  for (std::size_t k{0}; k < n; ++k) {
    a[k][0] = 1;
    std::size_t i = std::numeric_limits<std::size_t>::max();

    for (std::size_t m{1}; m < n; ++m) {
      ++i;

      if (i == k) {
        ++i;
      }

      const double d = source_points_table[k].x - source_points_table[i].x;
      a[k][m] = a[k][m - 1] / d;

      for (std::size_t j{m - 1}; j >= 1; --j) {
        a[k][j] = (a[k][j - 1] - a[k][j] * source_points_table[i].x) / d;
      }

      a[k][0] *= -1 * source_points_table[i].x / d;
    }
  }

  for (std::size_t i{0}; i < n; ++i) {
    double ci = 0;

    for (std::size_t k{0}; k < n; ++k) {
      ci += a[k][i] * source_points_table[k].y;
    }

    c[i] = ci;
  }

  return c;
}

function_values_table POL(const function_values_table& source_points_table,
                   std::size_t n,
                   const std::vector<double>& xes) {
  const auto c = POL(source_points_table, n);

  const auto k = xes.size();
  auto approximate_points_table = function_values_table(k);

  for (std::size_t i{0}; i < k; ++i) {
    const double x = xes[i];
    double y = 0;

    for (std::size_t j{0}; j < n; ++j) {
      y += c[j] * std::pow(x, j);
    }

    approximate_points_table[i] = point(x, y);
  }

  return approximate_points_table;
};

function_values_table create_source_table(int a, int b, std::size_t m) {
  std::cout << std::setw(9) << "X" << "\t" << std::setw(9) << "Y" << std::endl;

  auto source_points_table = function_values_table(m);
  for (std::size_t i{0}; i < m; ++i) {
    const double x = a + static_cast<double>(i) * (b - a) / (m - 1.0);
    const double y = f(x);
    source_points_table[i] = point(x, y);

    std::cout << std::setw(9) << x << "\t" << std::setw(9) << y << std::endl;
  }

  return source_points_table;
}

std::vector<double> create_approximation_table(int a, int b) {
  const std::size_t k{21};

  std::vector<double> xes = std::vector<double>(k);
  for (std::size_t j{0}; j < k; j++) {
    xes[j] = a + j * (b - a) / 20.0;
  }

  return xes;
}

void print_comparison_table(
  const function_values_table& approximated_points_table) {
  std::cout << std::endl;
  std::cout << std::setw(9) << "X" << "\t" << std::setw(9) << "Y" << "\t"
            << std::setw(9) << "Y'" << "\t" << std::setw(9) << "e" << std::endl;

  for (const auto& approximated_point : approximated_points_table) {
    double x = approximated_point.x,
      y = f(x),
      ya = approximated_point.y,
      e = std::fabs(ya - y);

    std::cout << std::setw(9) << x << "\t" << std::setw(9) << y << "\t"
              << std::setw(9) << ya << "\t" << std::setw(9) << e << std::endl;
  }
}

int main() {
  int a, b;
  std::size_t m, n;

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
  std::cout.precision(4);

  const function_values_table source_points_table = 
    create_source_table(a, b, m);
  const std::vector<double> xes = create_approximation_table(a, b);
  const function_values_table approximated_points_table =
    POL(source_points_table, n, xes);

  print_comparison_table(approximated_points_table);

  return EXIT_SUCCESS;
}
