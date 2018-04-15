// Copyright (c) 2017, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.

#include <iomanip>
#include <iostream>

#include "massive.h"

int main() {
  std::size_t n;
  std::cout << "Input array size: " << std::endl;
  std::cin >> n;

  std::cout << "Input first array: " << std::endl;

  using float_massive = massive<float>;

  float_massive first{n};
  std::cin >> first;

  std::cout << "First array: " << std::endl;
  std::cout << first << std::endl;

  std::cout << "Input second array: " << std::endl;

  float_massive second{n};
  std::cin >> second;

  std::cout << "Second array: " << std::endl;
  std::cout << second << std::endl;

  const float_massive third{first * second};
  std::cout << "Array composition: " << std::endl;
  std::cout << third << std::endl;

  return 0;
}