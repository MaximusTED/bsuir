// Copyright (c) 2016, Tsarevich A.U. aka maximus1642. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 2_2_1: User Functions.

#include <cstdlib>   // For EXIT_SUCCESS.
#include <iostream>
#include <vector>

#include "vector_processor.h"

int main() {
  std::size_t vector_size;
  int result_code = vector_processor::read_vector_size(vector_size);

  if (result_code != EXIT_SUCCESS) {
    std::cerr << "incorrect vector size." << std::endl;
    return result_code;
  }

  auto user_vector = std::vector<int>(vector_size);
  result_code = vector_processor::read_vector(user_vector, vector_size);

  if (result_code != EXIT_SUCCESS) {
    std::cerr << "can't read vector." << std::endl;
    return result_code;
  }

  int sum = 0;
  std::size_t count = 0;
  result_code = vector_processor::user_defined_process_vector(user_vector,
                                                              sum,
                                                              count);

  return vector_processor::notify_process_result(result_code, sum, count);
}