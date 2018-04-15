// Copyright (c) 2016, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 2.1: User Functions.

#include <cstdlib>  // For EXIT_SUCCESS.
#include <iostream>
#include <vector>

#include "vector_processor.h"

int main() {
  int result_code;
  std::size_t vector_size;
  std::tie(vector_size, result_code) = vector_processor::read_vector_size();

  if (result_code != EXIT_SUCCESS) {
    std::cerr << "Incorrect vector size." << std::endl;
    return result_code;
  }

  std::vector<int> user_vector;
  std::tie(user_vector, result_code) =
      vector_processor::read_vector<int>(vector_size);

  if (result_code != EXIT_SUCCESS) {
    std::cerr << "Can't read vector." << std::endl;
    return result_code;
  }

  int sum = 0;
  std::size_t count = 0;
  std::tie(sum, count, result_code) =
      vector_processor::user_defined_process_vector(user_vector);

  return vector_processor::notify_process_result(result_code, sum, count);
}
