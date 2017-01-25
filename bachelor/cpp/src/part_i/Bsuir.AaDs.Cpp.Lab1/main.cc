// Copyright (c) 2015, reginell. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 1: Linear algorithms. Math library.

#include <cmath>
#include <cstdlib>   // for EXIT_*
#include <iostream>

int main() {
  double x, y, z;

  std::cout << "x: "; std::cin >> x;
  std::cout << "y: "; std::cin >> y;
  std::cout << "z: "; std::cin >> z;

  const double a = std::fabs(std::cos(x) - std::cos(y)),
    c = 1 + 2 * std::pow(std::sin(y), 2),
    d = std::pow(a, c),
    b = 1 + z + std::pow(z, 2) / 2 + std::pow(z, 3) / 3 + std::pow(z, 4) / 4,
    s = d * b;

  std::cout << "function() = " << s << std::endl;

  return EXIT_SUCCESS;
}
