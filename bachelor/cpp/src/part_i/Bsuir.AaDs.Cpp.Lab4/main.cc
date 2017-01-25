// Copyright (c) 2015, reginell. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 4: Dimensional arrays.

#include <algorithm>
#include <array>
#include <cstdlib>   // for EXIT_*
#include <iostream>

template<typename T, typename Y>
constexpr inline T implicit_cast(const Y& value) {
  return value;
}

int main() {
  std::array<double, 100> array_to_sort;
  int raw_array_size;

  std::cout << "Type in array size: (ne bolshe "
            << array_to_sort.size()
            << "): ";
  std::cin >> raw_array_size;

  if (raw_array_size < 1 || 
      implicit_cast<std::size_t>(raw_array_size) > array_to_sort.size()) {
    std::cerr << "Razmer massiva dolgen bit' >= 1, no <= "
              << array_to_sort.size()
              << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Type in array items:" << std::endl;

  const std::size_t array_size = implicit_cast<std::size_t>(raw_array_size);

  for (std::size_t i = 0; i < array_size; i++) {
    std::cin >> array_to_sort[i];
  }

  std::cout << "Typed array:" << std::endl;

  for (std::size_t i = 0; i < array_size; i++) {
    std::cout << array_to_sort[i] << std::endl;
  }  

  // Veeery slow sort. O(1 / 2 * n * (n - 1)) ~ O(n^2).
  for (std::size_t g = 0; g < array_size - 1; g++) {
    std::size_t min_element_index = g;

    for (std::size_t i = g + 1; i < array_size; i++) {
      if (array_to_sort[min_element_index] > array_to_sort[i]) {
        min_element_index = i;
      }
    }

    std::swap(array_to_sort[g], array_to_sort[min_element_index]);
  }

  std::cout << "Sorted array:" << std::endl;

  for (std::size_t i = 0; i < array_size; i++) {
    std::cout << array_to_sort[i] << std::endl;
  }

  return EXIT_SUCCESS;
}
