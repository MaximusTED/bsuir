// Copyright (c) 2015, Tsarevich A.U. aka maximus1642. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 3: Cycles programming.

#include <cmath>
#include <iostream>
#include <iomanip>

int main() {
  double a, b;
  int n;

  std::cout << "a: "; std::cin >> a;
  std::cout << "b: "; std::cin >> b;
  std::cout << "n: "; std::cin >> n;

  double x = a;
  double h = (b - a) / 10;

  do {
    double s = 1, p = 1;

    for (int i = 1; i <= n; i++) {
      p *= (-x * x) / ((2.0 * i - 1) * (2 * i));
      s += p;
    }

    double y = cos(x);

    std::cout << std::setw(15) << x
              << std::setw(15) << y
              << std::setw(15) << s
              << std::setw(15) << y - s
              << std::endl;

    x += h;
  } while (x <= b);

  std::cout << std::endl;

  return 0;
}