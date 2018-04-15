// Copyright (c) 2015, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 4: Dimensional arrays.

#include <algorithm>  // std::swap
#include <array>      // std::array
#include <cstdlib>    // for EXIT_*
#include <iostream>

// Implicitly convert |value| from Y to T.
template <typename T, typename Y>
constexpr inline T implicit_cast(const Y& value) {
  return value;
}

int main() {
  using i32 = int;
  using usize = std::size_t;
  using f64 = double;

  std::array<f64, 100> array_to_sort;
  i32 raw_array_size;

  std::cout << "Type in array size: (less than or equal to "
            << array_to_sort.size() << "): ";
  if (!(std::cin >> raw_array_size)) {
    std::cerr << "Array size should be natural number." << std::endl;
    return EXIT_FAILURE;
  }

  const usize array_size = implicit_cast<usize>(raw_array_size);

  if (raw_array_size < 1 || array_size > array_to_sort.size()) {
    std::cerr << "Array size should be in range [1; " << array_to_sort.size()
              << "]." << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Type in array elements:" << std::endl;

  for (usize i{0}; i < array_size; i++) {
    if (!(std::cin >> array_to_sort[i])) {
      std::cerr << "Element should be real number with double precision."
                << std::endl;
      return EXIT_FAILURE;
    }
  }

  std::cout << "Typed array:" << std::endl;

  for (usize i{0}; i < array_size; i++) {
    std::cout << array_to_sort[i] << std::endl;
  }

  // Veeery slow sort. O(0.5 * n * (n - 1)) ~ O(n^2).
  for (usize g{0}; g < array_size - 1; g++) {
    usize min_element_index = g;

    for (usize i{g + 1}; i < array_size; i++) {
      if (array_to_sort[min_element_index] > array_to_sort[i]) {
        min_element_index = i;
      }
    }

    std::swap(array_to_sort[g], array_to_sort[min_element_index]);
  }

  std::cout << "Sorted array:" << std::endl;

  for (usize i{0}; i < array_size; i++) {
    std::cout << array_to_sort[i] << std::endl;
  }

  return EXIT_SUCCESS;
}
