// Copyright (c) 2015, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 5: Pointers. Programming Dynamic Two-dimensional Arrays.

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>

template <typename T, typename Y>
constexpr inline T implicit_cast(const Y& value) noexcept {
  return value;
}

template <class T>
using vec = std::vector<T, std::allocator<T>>;

int main() {
  using i32 = int;
  using usize = std::size_t;
  using f64 = double;

  i32 n, m;

  std::cout << "Vvedite razmeri matricy NxM: ";
  if (!(std::cin >> n >> m)) {
    std::cerr << "Razmeri doljni bit chelimi." << std::endl;
    return EXIT_FAILURE;
  }

  if (0 >= n || m <= 0) {
    std::cerr << "Nevernoe znachenie razmera." << std::endl;
    return EXIT_FAILURE;
  }

  const auto un{implicit_cast<usize>(n)}, um{implicit_cast<usize>(m)};

  auto mas{vec<vec<f64>>{un}};
  for (auto& item : mas) {
    item = vec<f64>(um);
  }

  for (usize i{0}; i < un; i++) {
    for (usize j{0}; j < um; j++) {
      std::cout << "Matrica [" << i + 1 << "][" << j + 1 << "]: ";
      if (!(std::cin >> mas[i][j])) {
        std::cerr << "Element dolzhen bit drobnim." << std::endl;
        return EXIT_FAILURE;
      }
    }
  }

  for (const auto& v : mas) {
    for (const auto& e : v) {
      std::cout << std::setw(6) << e;
    }

    std::cout << std::endl;
  }

  for (usize i{0}; i < um; i++) {
    f64 sum{0.0};

    for (const auto& v : mas) {
      sum += v[i];
    }

    for (const auto& v : mas) {
      const auto& elem = v[i];

      if (2.0 * elem > sum) {
        std::cout << "Osobij element stolbca " << i + 1 << ": " << elem
                  << std::endl;
      }
    }
  }

  return EXIT_SUCCESS;
}
