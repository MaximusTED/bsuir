// Copyright (c) 2015, Tsarevich A.U. aka maximus1642. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 4: Dimensional arrays.

#include <iostream> 

int main() {
  constexpr int array_max_size = 100;

  double array_to_sort[array_max_size];
  int array_size;

  std::cout << "Vvedite razmer massiva (ne bolshe " 
            << array_max_size 
            << "): ";
  std::cin >> array_size;

  if (array_size < 1 || array_size > array_max_size) {
    std::cerr << "Razmer massiva dolgen bit' >= 1, no <= "
              << array_max_size 
              << std::endl;
    return 1;
  }

  for (int i = 0; i < array_size; i++) {
    std::cout << "Vvedite "
              << i + 1 
              << "-j element: ";
    std::cin >> array_to_sort[i];
  }

  std::cout << "Vveden massiv:" << std::endl;

  for (int i = 0; i < array_size; i++) {
    std::cout << i + 1
              << "-j element = " 
              << array_to_sort[i] 
              << std::endl;
  }

  // Veeery slow sort. O(1 / 2 * n * (n - 1)) ~ O(n^2).
  for (int g = 0; g < array_size - 1; g++) {
    int min_element_index = g;

    for (int i = g + 1; i < array_size; i++) {
      if (array_to_sort[min_element_index] > array_to_sort[i]) {
        min_element_index = i;
      }
    }

    double swap_element = array_to_sort[g];
    double min_element = array_to_sort[min_element_index];

    if (swap_element != min_element) {
      array_to_sort[g] = min_element;
      array_to_sort[min_element_index] = swap_element;
    }
  }

  std::cout << "Resultat:" << std::endl;

  for (int i = 0; i < array_size; i++) {
    std::cout << i + 1
              << "-j element = "
              << array_to_sort[i] 
              << std::endl;
  }

  return 0;
}