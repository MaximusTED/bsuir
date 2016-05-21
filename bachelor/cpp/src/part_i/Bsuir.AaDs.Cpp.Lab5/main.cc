// Copyright (c) 2015, reginell. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 5: Pointers. Programming Dynamic Two-dimensional Arrays.

#include <iostream>
#include <iomanip>

template<typename T, typename Y>
inline T implicit_cast(Y value) {
  return value;
}

int main() {
  int n, m;

  std::cout << "Vvedite razmeri matricy NxM: ";
  std::cin >> n >> m;

  if (0 >= n || m <= 0) {
    std::cerr << "Nevernoe znachenie razmera." << std::endl;
    return 1;
  }

  std::size_t un = implicit_cast<std::size_t>(n), 
              um = implicit_cast<std::size_t>(m);

  double **mas = new double*[un];
  for (std::size_t i = 0; i < un; i++)
    mas[i] = new double[um];

  for (std::size_t i = 0; i < un; i++) {
    for (std::size_t j = 0; j < um; j++) {
      std::cout << "Matrica [" << i + 1 << "]["
           << j + 1 << "]: ";
      std::cin >> mas[i][j];
    }
  }

  for (std::size_t i = 0; i < un; i++) {
    for (std::size_t j = 0; j < um; j++)
      std::cout << std::setw(6) << mas[i][j];

    std::cout << std::endl;
  }

  for (std::size_t i = 0; i < um; i++) {
    double sum = 0;

    for (std::size_t k = 0; k < un; k++)
      sum += mas[k][i];

    for (std::size_t g = 0; g < un; g++) {
      if (2 * mas[g][i] > sum) {
        std::cout << "Osobij element stolbca " << i + 1 << ": "
                  << mas[g][i] << std::endl;
      }
    }
  }

  for (std::size_t i = 0; i < un; i++)
    delete[] mas[i];

  delete[] mas;

  return 0;
}