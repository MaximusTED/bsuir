// Copyright (c) 2015, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 8: Programming with functions.

#include <iostream>

#include "user_defined_functions.h"

int main() {
  using namespace functions;

  f64 a, b, h, eps;

  std::cout << "a, b, h, eps: ";
  std::cin >> a >> b >> h >> eps;

  PrintFuncValuesTable(a, b, h, eps, NinePowerX, 'y');

  std::cout << std::endl;

  PrintFuncValuesTable(a, b, h, eps, MultLog9X, 's');

  return 0;
}