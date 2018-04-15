// Copyright (c) 2015, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 3: Cycles programming.

#include <cmath>
#include <cstdint>
#include <cstdlib>  // for EXIT_*
#include <iomanip>
#include <iostream>

int main() {
  using i32 = int;
  using f64 = double;

  f64 a, b;
  i32 n;

  std::cout << "a: ";
  std::cin >> a;
  std::cout << "b: ";
  std::cin >> b;
  std::cout << "n: ";
  std::cin >> n;

  f64 x{a};
  const f64 h{(b - a) / 10};

  std::cout.width(15);

  do {
    f64 s{1}, p{1};

    for (int i{1}; i <= n; i++) {
      p *= (-x * x) / ((2.0 * i - 1) * (2 * i));
      s += p;
    }

    const f64 y{cos(x)};

    std::cout << x << y << s << y - s << std::endl;

    x += h;
  } while (x <= b);

  std::cout << std::endl;

  return EXIT_SUCCESS;
}
