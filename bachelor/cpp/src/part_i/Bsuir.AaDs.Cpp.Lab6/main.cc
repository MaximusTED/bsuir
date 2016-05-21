// Copyright (c) 2015, reginell. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 6: Programming with Strings.

#include <iostream>

int main() {
  char input_string[32];
  int input_count = sizeof(input_string) / sizeof(input_string[0]);

  std::cout << "Vvedite stroku sostojashchuju iz 0 i 1: ";
  std::cin.getline(input_string, input_count);

  for (int i = 0; input_string[i] != '\0'; i++) {
    if (input_string[i] != '0' && input_string[i] != '1') {
      std::cout << "Nekorrektnij vvod: " << input_string[i];
      return 1;
    }
  }

  for (int i = 0; input_string[i] != '\0'; i++) {
    int group_zero_count = 0;
    while (input_string[i] == '0') {
      ++group_zero_count;
      ++i;
    }
    if (group_zero_count != 0 && group_zero_count % 2 == 0) {
      while (group_zero_count-- > 0) {
        std::cout << '0';
      }
      std::cout << std::endl;
    }

    int group_one_count = 0;
    while (input_string[i] == '1') {
      ++group_one_count;
      ++i;
    }
    if (group_one_count != 0 && group_one_count % 2 == 0) {
      while (group_one_count-- > 0) {
        std::cout << '1';
      }
      std::cout << std::endl;
    }

    --i;
  }

  return 0;
}