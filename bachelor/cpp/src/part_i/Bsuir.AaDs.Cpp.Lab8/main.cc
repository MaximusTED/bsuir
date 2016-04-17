// Copyright (c) 2015, Tsarevich A.U. aka maximus1642. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 8: Programming with functions.

#include <iostream>

#include "user_defined_functions.h"

int main() {
  double a, b, h, eps;
  
  std::cout << "a, b, h, eps: ";
  std::cin >> a >> b >> h >> eps;

  functions::PrintFuncValuesTable(a, b, h, eps, functions::NinePowerX, 'y');

  std::cout << std::endl;

  functions::PrintFuncValuesTable(a, b, h, eps, functions::MultLog9X, 's');

  return 0;
}