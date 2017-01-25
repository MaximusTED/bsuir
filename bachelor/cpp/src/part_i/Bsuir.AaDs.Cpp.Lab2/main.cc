// Copyright (c) 2015, reginell. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 2: Programming branching algorithms.

#include <array>
#include <cmath>
#include <cstdlib>   // for EXIT_*
#include <iostream>

int main() {
  using single_argument_function_ptr = double(*)(double);
  const std::array<single_argument_function_ptr, 3> single_argument_functions = 
  {
    [](double x) { return std::sinh(x); },
    [](double x) { return std::pow(x, 2); },
    [](double x) { return std::exp(x); }
  };

  double x, y;
  std::size_t k;

  std::cout << "x: "; std::cin >> x;
  std::cout << "y: "; std::cin >> y;
  std::cout << "f [1 -> sh(x), 2 -> x^2, 3 -> exp(x)]: "; std::cin >> k;

  if (k == 0 || k > single_argument_functions.size()) {
    std::cerr << "The function is not choosen. Value "
              << k
              << " is not in the set of available ones: "
              << "[" << 1 << "; " << single_argument_functions.size() << "]"
              << std::endl;
    return EXIT_FAILURE;
  }

  const double f = (*single_argument_functions[k - 1])(x);

  using three_argument_function_ptr = double(*)(double x, double y, double f);
  const std::array<three_argument_function_ptr, 3> three_argument_functions =
  {
    [](double, double y, double f) { 
      return std::pow(std::fabs(f - y), 1 / 3.) + std::tan(f);
    },
    [](double, double y, double f) {
      return std::pow(y - f, 3) + std::cos(f);
    },
    [](double x, double y, double f) { 
      return std::pow(y + f, 2) + std::pow(x, 3);
    }
  };

  const std::size_t i = x > y ? 0 : (x < y ? 1 : 2);
  const double d = (*three_argument_functions[i])(x, y, f);

  std::cout << "function() = " << d << std::endl;

  return EXIT_SUCCESS;
}
