// Copyright (c) 2015, reginell. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 1: Linear algorithms. Math library.

#include <cmath>
#include <iostream>

int main() {
  double x, y, z;

  std::cout << "x: "; std::cin >> x;
  std::cout << "y: "; std::cin >> y;
  std::cout << "z: "; std::cin >> z;

  double a = fabs(cos(x) - cos(y));
  double c = 1 + 2 * pow(sin(y), 2);

  double d = pow(a, c);
  double b = 1 + z + pow(z, 2) / 2 + pow(z, 3) / 3 + pow(z, 4) / 4;
  double s = d * b;

  std::cout << "function() = " << s << std::endl;

  return 0;
}