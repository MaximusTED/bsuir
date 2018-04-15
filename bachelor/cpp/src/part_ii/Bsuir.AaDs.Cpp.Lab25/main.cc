// Copyright (c) 2016, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).

#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

using usize = std::size_t;
using i32 = int;
using f64 = double;

template <typename T, typename Y>
constexpr inline T implicit_cast(const Y& value) noexcept {
  return value;
}

template <class T>
using vec = std::vector<T, std::allocator<T>>;

f64 f(f64 x) noexcept { return std::pow(x, 2) + 5 * std::cos(x) - 3; }

f64 MD(f64 a, f64 b, f64 e) noexcept {
  f64 x[3], y[3];
  x[0] = a;
  x[1] = b;
  y[0] = f(x[0]);

  do {
    x[2] = (x[0] + x[1]) / 2;
    y[2] = f(x[2]);
    f64 v = y[0] * y[2];

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
  i32 a, b;
  f64 m, e;

  std::cout << "a = ";
  std::cin >> a;
  std::cout << "b = ";
  std::cin >> b;
  std::cout << "m = ";
  std::cin >> m;
  std::cout << "e = ";
  std::cin >> e;

  const f64 h{(b - a) / m};
  f64 X = a;
  f64 y{f(X)};

  std::cout.flags(std::ios::right);
  std::cout.precision(4);  //-V112

  std::cout << std::setw(9) << "X"
            << "\t" << std::setw(9) << "Y" << std::endl;
  std::cout << std::setw(9) << X << "\t" << std::setw(9) << y << std::endl;

  X += h;
  f64 u{y};

  auto z = vec<f64>(implicit_cast<usize>(m) + 1);
  usize i{0};

  while (X <= b) {
    y = f(X);
    std::cout << std::setw(9) << X << "\t" << std::setw(9) << y << std::endl;

    if ((u > 0 && y < 0) || (u < 0 && y > 0)) {
      z[i++] = MD(X - h, X, e);
    }

    u = y;
    X += h;
  }

  const usize k{i};
  std::cout << std::endl;

  for (i = 0; i < k; i++)
    std::cout << "X" << i + 1 << " = " << z[i] << ", e = " << std::fabs(f(z[i]))
              << std::endl;

  return 0;
}
