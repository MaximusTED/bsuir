// Lab 5: Templates.

#include <iostream>
#include <iomanip>

#include "massive.h"

int main() {
  std::size_t n;
  std::cout << "Input array size: " << std::endl;
  std::cin >> n;

  std::cout << "Input first array: " << std::endl;
  
  using float_massive = massive<float>;
  
  float_massive first{n};
  std::cin >> first;

  std::cout << "First array: " << std::endl;
  std::cout << first << std::endl;

  std::cout << "Input second array: " << std::endl;
  
  float_massive second{n};
  std::cin >> second;

  std::cout << "Second array: " << std::endl;
  std::cout << second << std::endl;

  const massive<float> third{first * second};
  std::cout << "Array composition: " << std::endl;
  std::cout << third << std::endl;

  return 0;
}