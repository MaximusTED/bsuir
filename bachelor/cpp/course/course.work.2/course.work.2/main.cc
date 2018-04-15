// Copyright (c) 2017, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.
//
// 4th Term Project: Function Calculation

// Cross-platform CRT.
#define _CRT_SECURE_NO_WARNINGS
// Smaller type checks can't work with STL.
#define _ALLOW_RTCc_IN_STL

#include <cassert>
#include <cerrno>  // errno
#include <cmath>
#include <cstdint>
#include <cstring>     // strerror
#include <functional>  // std::function
#include <iomanip>
#include <iostream>
#include <limits>
#include <tuple>

// Alias frequently used types to up code read time.
using u32 = uint32_t;
using f32 = float;
static_assert(sizeof(f32) == 4,
              "f32 should be floating-point value with 4 bytes length.");
using err = int;

// Success error code. Why errno doesn't define smth like this?
constexpr err EOK = 0;

// Saves errno at the beginning of the scope, restore on out of scope. 
class ScopedErrno {
 public:
  ScopedErrno() noexcept : error_{errno} {}
  ~ScopedErrno() noexcept { errno = error_; }

 private:
  const err error_;

  ScopedErrno(const ScopedErrno &s) = delete;
  ScopedErrno(const ScopedErrno &&s) = delete;
  ScopedErrno& operator=(const ScopedErrno &s) = delete;
  ScopedErrno& operator=(const ScopedErrno &&s) = delete;
};

// Computes sum of |sum_func| applied on [0, n].
inline std::tuple<f32, err> sum(
    u32 n, std::function<std::tuple<f32, err>(u32)> sum_func) noexcept {
  // Do not introduce errno side effects, return error explicitly.
  ScopedErrno scoped_errno;

  // Incorrect sum index range.
  if (n == 0 || n == std::numeric_limits<u32>::max()) {
    return {0.0f, EDOM};
  }

  f32 result{0.0f};

  for (u32 k{1}; k <= n; ++k) {
    auto [sum, error] = sum_func(k);

    // Check for errors during sum function evaluation.
    if (error != EOK) return {0.0f, error};

    // Check for sum value overflow (> max(typeof(sum))).
    // TODO(reginell): Change overflow checking to reduce computations count.
    if (std::numeric_limits<f32>::max() - sum < result) {
      return {0.0f, ERANGE};
    }

    result += sum;
  }

  return {result, EOK};
}

// Computes  
std::tuple<f32, err> f(u32 n, f32 x) noexcept {
  // Do not introduce errno side effects, return error explicitly.
  ScopedErrno scoped_errno;

  // Cache exponent.
  const f32 exponent{std::exp(x)};

  // Exponent calculation errors.
  if (errno != EOK) return {0.0f, errno};

  const f32 radix{std::pow(exponent + 1 / exponent, 1 / 3.0f)};

  // Pow calculation errors.
  if (errno != EOK) return {0.0f, errno};

  // Cache sqrt.
  const f32 sqrt{std::sqrt(x)};

  // Sqrt calculation errors.
  if (errno != EOK) return {0.0f, errno};

  auto [sum_value, sum_error] = sum(n, [x, sqrt](u32 k) noexcept -> std::tuple<f32, err> {
    // Should be impossible.
    assert(k != 0);

    // .. but still check.
    if (k == 0) return {0.0f, ERANGE};

    const f32 result{sqrt / k + std::sin(std::log(k + x) / k)};

    // result calculation can fail.
    if (errno != EOK) return {0.0f, errno};

    return {result, EOK};
  });

  if (sum_error != EOK) return {0.0f, sum_error};

  // Overflow during multiplication.
  // TODO(reginell): Change overflow computation to compute result and check
  // overflow at the same time.
  if (std::numeric_limits<f32>::max() / radix < sum_value) {
    return {0.0f, ERANGE};
  }

  return {radix * sum_value, EOK};
}

int main() {
  // TODO(reginell): Add test suite, for example using gtest.

  for (u32 n = 10; n <= 15; ++n) {
    std::cout << "N = " << n << ":" << std::endl;

	for (u32 i{60}; i <= 110; i += 25) {
      const f32 x{i / 100.f};
      auto [value, error] = f(n, x);

      std::cout << "X = " << std::setw(4) << x << ", f(N, X) = ";

      if (error == EOK) {
        std::cout << value << std::endl;
      } else {
        std::cerr << std::strerror(error) << std::endl;
      }
    }

    std::cout << std::endl;
  }

  return EOK;
}