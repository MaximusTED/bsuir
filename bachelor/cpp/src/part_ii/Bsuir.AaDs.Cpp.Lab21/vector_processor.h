// Copyright (c) 2016, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 2_1: User Functions.

#ifndef BSUIR_AADS_CPP_LAB1_2_VECTOR_PROCESSOR_H_
#define BSUIR_AADS_CPP_LAB1_2_VECTOR_PROCESSOR_H_

#include <cstddef>  // For std::size_t.
#include <ctime>
#include <tuple>
#include <vector>

namespace vector_processor {

enum ProcessError { kNoFirstPositive = 1, KNoSecondPositive };

namespace details {

inline int random_value() noexcept {
  constexpr int kLowerBound = -100;
  constexpr int kUpperBound = 100;

  static_assert(kLowerBound <= kUpperBound,
                "Lower bound should be <= upper bound.");

  return kLowerBound + rand() % (kUpperBound - kLowerBound + 1);
}

}  // namespace details.

/**
 * Prompts user for and reads vector size.
 * @return std::tuple<std::size_t, int> where first param is the read vector
 * size & second is error code (EXIT_SUCCESS on success, otherwise failure
 * code).
 */
std::tuple<std::size_t, int> read_vector_size();

/**
 * Prompts user and reads vector.
 *
 * Vector can be read in two modes: manual (from input stream) and random (from)
 * random device. For random input you can initi
 *
 * @param [out] user_vector The vector to read. It's size should be at least
 *   vector_size.
 * @param [in] vector_size The count of vector elements are expected to be read.
 * @return std::tuple<std::size_t, int> where first param is the vector to read
 * & second one is error code (EXIT_SUCCESS on success, otherwise failure code).
 */
template <typename T>
std::tuple<std::vector<T>, int> read_vector(const std::size_t vector_size) {
  auto fill_type{0};

  std::cout << "Vector fill type (1 - random, 2 - manual type): ";
  std::cin >> fill_type;

  auto user_vector = std::vector<T>{};
  user_vector.resize(vector_size);

  switch (fill_type) {
    case 1:
      std::srand(static_cast<unsigned int>(std::time(nullptr)));

      for (auto& item : user_vector) {
        item = details::random_value();
      }
      break;

    case 2:
      for (auto& item : user_vector) {
        if (!(std::cin >> item)) {
          std::cerr << "Vector element should be int." << std::endl;
          return std::make_tuple(user_vector, -EINVAL);
        }
      }
      break;

    default:
      std::cerr << "Incorrect fill type. Allowed values: 1, 2." << std::endl;
      return std::make_tuple(user_vector, -EINVAL);
  }

  return std::make_tuple(user_vector, EXIT_SUCCESS);
}

/**
 * Finds sum and count of vector elements between first and last positive ones.
 *
 * @param [in] user_vector The vector to process.
 * @param [out] sum The sum of vector elements between first and last positive
 *   ones.
 * @param [out] count
 * @return std::tuple<T, std::size_t, int> where
 *   T is the sum of vector elements between first and last positive ones.
 *   std::size_t is the count of vector elements between first and last
 *     positive ones.
 *   int is EXIT_SUCCESS on success, otherwise failure code.
 */
template <typename T>
std::tuple<T, std::size_t, int> user_defined_process_vector(
    const std::vector<T>& user_vector) {
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
    return std::make_tuple(T{}, 0, -kNoFirstPositive);
  }

  auto last_positive_index = kMaxPositiveIndex;

  for (std::size_t i = array_size - 1; i > first_positive_index; i--) {
    if (user_vector[i] > 0) {
      last_positive_index = i;
      break;
    }
  }

  if (last_positive_index == kMaxPositiveIndex) {
    return std::make_tuple(T{}, 0, -KNoSecondPositive);
  }

  T sum = {};
  std::size_t count = {};

  for (auto i = first_positive_index + 1; i < last_positive_index; i++) {
    ++count;
    sum += user_vector[i];
  }

  return std::make_tuple(sum, count, EXIT_SUCCESS);
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
template <typename T>
int notify_process_result(int result_code, T sum, std::size_t count) {
  switch (result_code) {
    case EXIT_SUCCESS:
      std::cout << "Sum between first and last positive values: " << sum
                << std::endl;
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
      std::cerr << "Unknown processing result: " << result_code << std::endl;
      break;
  }

  return result_code;
}

}  // namespace vector_processor.

#endif  // !BSUIR_AADS_CPP_LAB1_2_VECTOR_PROCESSOR_H_
