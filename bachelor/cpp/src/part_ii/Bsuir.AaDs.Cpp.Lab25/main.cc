// Copyright (c) 2016, reginell. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).

#include <cmath>
#include <cstddef>
#include <iostream>
#include <iomanip>
#include <vector>

double f(double x) {
  return std::pow(x, 2) + 5 * std::cos(x) - 3;
}

double MD(double a, double b, double e) {
  double x[3], y[3];
  x[0] = a;
  x[1] = b;
  y[0] = f(x[0]);

  do {
    x[2] = (x[0] + x[1]) / 2;
    y[2] = f(x[2]);
    double v = y[0] * y[2];

    if (v > 0) {
      x[0] = x[2];
      y[0] = y[2];
    } else {
      x[1] = x[2];
      y[1] = y[2];
    }
  } while ((x[1] - x[0]) > e);

  return (x[0] + x[1]) / 2;
}

int main() {
  int a, b;
  double m, e;

  std::cout << "a = ";
  std::cin >> a;
  std::cout << "b = ";
  std::cin >> b;
  std::cout << "m = ";
  std::cin >> m;
  std::cout << "e = ";
  std::cin >> e;

  const double h{(b - a) / m};
  double X = a;
  double y{f(X)};

  std::cout.flags(std::ios::right);
  std::cout.precision(4);

  std::cout << std::setw(9) << "X" << "\t" << std::setw(9) << "Y" << std::endl;
  std::cout << std::setw(9) << X << "\t" << std::setw(9) << y << std::endl;

  X += h;
  double u{y};

  std::vector<double> z = std::vector<double>(static_cast<std::size_t>(m) + 1);
  std::size_t i{0};

  while (X <= b) {
    y = f(X);
    std::cout << std::setw(9) << X << "\t" << std::setw(9) << y << std::endl;

    if ((u > 0 && y < 0) || (u < 0 && y > 0)) {
      z[i++] = MD(X - h, X, e);
    }

    u = y;
    X += h;
  }

  const std::size_t k{i};
  std::cout << std::endl;

  for (i = 0; i < k; i++)
    std::cout << "X" << i + 1 << " = " << z[i]
              << ", e = " << std::fabs(f(z[i])) << std::endl;

  return 0;
}
