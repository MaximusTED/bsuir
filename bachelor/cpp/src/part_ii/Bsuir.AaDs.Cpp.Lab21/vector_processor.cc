// Copyright (c) 2016, reginell. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 2_1: User Functions.

#include "vector_processor.h"

#include <cerrno>
#include <cstdlib>   // For EXIT_SUCCESS.
#include <iostream>

namespace vector_processor {

int read_vector_size(std::size_t &vector_size) {
  int raw_vector_size;

  std::cout << "vector size: ";
  if (!(std::cin >> raw_vector_size)) {
    std::cerr << "vector size should be int." << std::endl;
    return -EINVAL;
  }

  if (raw_vector_size <= 0) {
    std::cerr << "vector size " << raw_vector_size
      << "should be positive." << std::endl;
    return -EINVAL;
  }

  vector_size = static_cast<std::size_t>(raw_vector_size);
  return EXIT_SUCCESS;
}

}  // namespace vector_processor.
