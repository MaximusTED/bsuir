// Copyright (c) 2016, reginell. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 2_1: User Functions.

#ifndef BSUIR_AADS_CPP_LAB1_2_VECTOR_PROCESSOR_H_
#define BSUIR_AADS_CPP_LAB1_2_VECTOR_PROCESSOR_H_

#include <cstddef>   // For std::size_t.
#include <ctime>
#include <vector>

namespace vector_processor {

enum ProcessError {
  kNoFirstPositive = 1,
  KNoSecondPositive
};

namespace details {

inline int random_value() {
  constexpr int kLowerBound = -100;
  constexpr int kUpperBound = 100;

  static_assert(kLowerBound <= kUpperBound, "Lower bound should be <= upper bound.");

  return kLowerBound + rand() % (kUpperBound - kLowerBound + 1);
}

}  // namespace details.

/**
 * Prompts user for and reads vector size.
 * @param [in] vector_size The read vector size.
 * @return EXIT_SUCCESS on success, otherwise failure code.
 */
int read_vector_size(std::size_t &vector_size);

/**
 * Prompts user and reads vector.
 *
 * Vector can be read in two modes: manual (from input stream) and random (from)
 * random device. For random input you can initi
 *
 * @param [out] user_vector The vector to read. It's size should be at least
 *   vector_size.
 * @param [in] vector_size The count of vector elements are expected to be read.
 * @return EXIT_SUCCESS on success, otherwise failure code.
 */
template<typename T>
int read_vector(std::vector<T> &user_vector, std::size_t vector_size) {
  int fill_type = 0;

  std::cout << "vector fill type (1 - random, 2 - manual type): ";
  std::cin >> fill_type;

  switch (fill_type) {
  case 1:
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (std::size_t i = 0; i < vector_size; i++) {
      user_vector[i] = details::random_value();
      std::cout << i + 1 << " element: " << user_vector[i] << std::endl;
    }
    break;

  case 2:
    for (std::size_t i = 0; i < vector_size; i++) {
      std::cout << i + 1 << " element: ";
      if (!(std::cin >> user_vector[i])) {
        std::cerr << "vector element should be int." << std::endl;
        return -EINVAL;
      }
    }
    break;

  default:
    std::cerr << "incorrect fill type. Allowed values: 1, 2." << std::endl;
    return -EINVAL;
  }

  return EXIT_SUCCESS;
}

/**
 * Finds sum and count of vector elements between first and last positive ones.
 *
 * @param [in] user_vector The vector to process.
 * @param [out] sum The sum of vector elements between first and last positive
 *   ones.
 * @param [out] count The count of vector elements between first and last
 *   positive ones.
 * @return EXIT_SUCCESS on success, otherwise failure code.
 */
template<typename T>
int user_defined_process_vector(const std::vector<T> &user_vector,
                                T &sum,
                                std::size_t &count) {
  sum = {};
  count = 0;

  const auto array_size = user_vector.size();
  constexpr auto kMaxPositiveIndex = std::numeric_limits<std::size_t>::max();

  auto first_positive_index = kMaxPositiveIndex;

  for (std::size_t i = 0; i < array_size; i++) {
    if (user_vector[i] > 0) {
      first_positive_index = i;
      break;
    }
  }

  if (first_positive_index == kMaxPositiveIndex) {
    return -kNoFirstPositive;
  }

  auto last_positive_index = kMaxPositiveIndex;

  for (std::size_t i = array_size - 1; i > first_positive_index; i--) {
    if (user_vector[i] > 0) {
      last_positive_index = i;
      break;
    }
  }

  if (last_positive_index == kMaxPositiveIndex) {
    return -KNoSecondPositive;
  }

  for (auto i = first_positive_index + 1; i < last_positive_index; i++) {
    ++count;
    sum += user_vector[i];
  }

  return EXIT_SUCCESS;
}

/**
 * Prints descripton message for result code and user_defined_process_vector
 * function results.
 *
 * @param [in] result_code The result code from user_defined_process_vector
 *   function.
 * @param [in] sum The sum of vector elements.
 * @param [in] count The count of vector elements.
 * @return result_code.
 */
template<typename T>
int notify_process_result(int result_code, T sum, std::size_t count) {
  switch (result_code) {
  case EXIT_SUCCESS:
    std::cout << "Sum between first and last positive values: "
      << sum << std::endl;
    std::cout << "Count of elements between first and last positive values: "
      << count << std::endl;
    break;

  case -kNoFirstPositive:
    std::cerr << "There is no positive elements." << std::endl;
    break;

  case -KNoSecondPositive:
    std::cerr << "There is no second positive element." << std::endl;
    break;

  default:
    std::cerr << "unknown processing result: "
      << result_code << std::endl;
    break;
  }

  return result_code;
}

}  // namespace vector_processor.

#endif // !BSUIR_AADS_CPP_LAB1_2_VECTOR_PROCESSOR_H_
