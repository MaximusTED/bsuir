// Copyright (c) 2015, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 8: Programming with Functions.

#include "user_defined_functions.h"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace functions {

void PrintFuncValuesTable(f64 a, f64 b, f64 h, f64 eps, TestedFunction func,
                          char func_name) {
  std::cout << std::setw(12) << "x" << std::setw(15) << func_name << "(x)"
            << std::setw(10) << "k" << std::endl;

  i32 k = 0;
  for (f64 x = a; x < b + h / 2; x += h) {
    const f64 sum = (*func)(x, eps, k);

    std::cout << std::setw(12) << x << std::setw(15) << sum << std::setw(10)
              << k << std::endl;
  }
}

f64 NinePowerX(f64 x, f64 eps, i32 &k) { return pow(9, x); }

f64 MultLog9X(f64 x, f64 eps, i32 &k) {
  const f64 log9 = log(9);
  f64 a = 1, c = x, sum = 1;

  k = 1;

  while (fabs(c) > eps) {
    c = log9 * x / k++;
    sum += (a *= c);
  }

  return sum;
}

}  // namespace functions.
