// Copyright (c) 2015, Tsarevich A.U. aka maximus1642. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 2: Programming branching algorithms.

#include <cmath>
#include <iostream>

int main() {
  double x, y;
  int k;

  std::cout << "x: "; std::cin >> x;
  std::cout << "y: "; std::cin >> y;
  std::cout << "f [1 -> sh(x), 2 -> x^2, 3 -> exp(x)]: "; std::cin >> k;

  double f;

  switch (k) {
    case 1: 
      f = sinh(x);
      break;
    case 2: 
      f = pow(x, 2);
      break;
    case 3: 
      f = exp(x);
      break;
    default:
      std::cerr << "The function is not choosen. Value "
                << k
                << " is not in the set of available ones: "
                << "[" << 1 << "; " << 3 << "]"
                << std::endl;
      return 1;
  }

  double d;

  if (x > y) {
    d = pow(fabs(f - y), 1 / 3.) + tan(f);
  } else if (x < y) {
    d = pow(y - f, 3) + cos(f);
  } else {
    d = pow(y + f, 2) + pow(x, 3);
  }

  std::cout << "function() = " << d << std::endl;
  
  return 0;
}