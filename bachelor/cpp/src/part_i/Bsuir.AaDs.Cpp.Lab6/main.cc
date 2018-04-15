// Copyright (c) 2015, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 6: Programming with Strings.

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>

int main() {
  using str = std::string;
  using usize = std::size_t;

  str input_string;

  std::cout << "Vvedite stroku sostojashchuju iz 0 i 1: ";
  std::getline(std::cin, input_string);

  const auto incorrect_value =
      std::find_if(std::cbegin(input_string), std::cend(input_string),
                   [](char c) { return c != '0' && c != '1'; });

  if (incorrect_value != std::cend(input_string)) {
    std::cerr << "Nekorrektnij vvod: " << *incorrect_value;
    return EXIT_FAILURE;
  }

  const usize length{input_string.length()};
  for (usize i{0}; i < length; i++) {
    auto group_zero_count =
        std::count_if(std::cbegin(input_string) + i, std::cend(input_string),
                      [](const char i) { return i == '0'; });

    i += group_zero_count;

    if (group_zero_count != 0 && group_zero_count % 2 == 0) {
      while (group_zero_count-- > 0) {
        std::cout << '0';
      }
      std::cout << std::endl;
    }

    auto group_one_count =
        std::count_if(input_string.cbegin() + i, input_string.cend(),
                      [](const char i) { return i == '1'; });

    i += group_one_count;

    if (group_one_count != 0 && group_one_count % 2 == 0) {
      while (group_one_count-- > 0) {
        std::cout << '1';
      }
      std::cout << std::endl;
    }

    --i;
  }

  return EXIT_SUCCESS;
}
