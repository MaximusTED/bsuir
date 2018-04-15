// Copyright (c) 2016, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 2_1: User Functions.

#include "vector_processor.h"

#include <cerrno>
#include <cstdlib>  // For EXIT_SUCCESS.
#include <iostream>

namespace vector_processor {

std::tuple<std::size_t, int> read_vector_size() {
  std::size_t vector_size;

  std::cout << "Vector size: ";
  if (!(std::cin >> vector_size)) {
    std::cerr << "Vector size should be int." << std::endl;
    return std::make_tuple(0, -EINVAL);
  }

  if (vector_size == 0) {
    std::cerr << "Vector size " << vector_size << "Should be positive."
              << std::endl;
    return std::make_tuple(0, -EINVAL);
  }

  return std::make_tuple(vector_size, EXIT_SUCCESS);
}

}  // namespace vector_processor.
