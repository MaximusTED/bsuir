// Copyright (c) 2015, reginell. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 8: Programming with Functions.

#include "user_defined_functions.h"

#include <cmath>
#include <iostream>
#include <iomanip>

namespace functions {

void PrintFuncValuesTable(double a, double b, double h, double eps, TestedFunction func, char func_name) {
  std::cout << std::setw(12) << "x"
    << std::setw(15) << func_name << "(x)"
    << std::setw(10) << "k"
    << std::endl;

  int k = 0;
  for (double x = a; x < b + h / 2; x += h) {
    double sum = (*func)(x, eps, k);
    std::cout << std::setw(12) << x
      << std::setw(15) << sum
      << std::setw(10) << k
      << std::endl;
  }
}

double NinePowerX(double x, double eps, int &k) {
  return pow(9, x);
}

double MultLog9X(double x, double eps, int &k) {
  double a = 1, c = x, sum = 1, log9 = log(9);
  k = 1;

  while (fabs(c) > eps) {
    c = log9 * x / k++;
    sum += (a *= c);
  }

  return sum;
}

}  // namespace functions.
