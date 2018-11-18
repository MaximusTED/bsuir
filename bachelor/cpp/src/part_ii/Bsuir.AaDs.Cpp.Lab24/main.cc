// Copyright (c) 2016, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 2.4: Derivative / i32egral functions approximation.

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <tuple>
#include <vector>

using f64 = double;
using i32 = int;
using usize = std::size_t;

template <class T>
using vec = std::vector<T, std::allocator<T>>;

f64 f(f64 x) noexcept { return std::pow(x, 2) + 5 * std::cos(x); }

vec<f64> dY_precise(const vec<f64>& X) {
  const usize n = X.size();
  auto DY = vec<f64>(n);

  // Точное значение 1 производной.
  for (usize i = 0; i < n; i++) DY[i] = 2 * X[i] - 5 * std::sin(X[i]);

  return DY;
}

vec<f64> d2Y_precise(const vec<f64>& X) {
  const usize n = X.size();
  auto D2Y = vec<f64>(n);

  // Точное значение 2 производной.
  for (usize i = 0; i < n; i++) D2Y[i] = 2 - 5 * std::cos(X[i]);

  return D2Y;
}

f64 integral_precise(f64 x) noexcept { return std::pow(x, 3) / 3 + 5 * std::sin(x); }

f64 integral_precise(f64 a, f64 b) {
  return integral_precise(b) - integral_precise(a);
}

vec<f64> dY_approximate(const vec<f64>& Y, f64 h) {
  const usize n = Y.size();
  vec<f64> dY = vec<f64>(n);

  // Аппроксимация первой производной в крайних точках.
  dY[0] = -(3 * Y[0] - 4 * Y[1] + Y[2]) / (2 * h);                 //-V112
  dY[n - 1] = (Y[n - 3] - 4 * Y[n - 2] + 3 * Y[n - 1]) / (2 * h);  //-V112

  // Аппроксимация первой производной в остальных точках.
  for (usize i = 1; i < n - 1; i++) dY[i] = (Y[i + 1] - Y[i - 1]) / (2 * h);

  return dY;
}

vec<f64> d2Y_approximate(const vec<f64>& Y, f64 h) {
  const usize n = Y.size();
  vec<f64> d2Y = vec<f64>(n);

  // В крайних точках не считаем.
  d2Y[0] = d2Y[n - 1] = std::nan("");

  // Аппроксимация второй производной.
  for (usize i = 1; i < n - 1; i++)
    d2Y[i] = (Y[i - 1] - 2 * Y[i] + Y[i + 1]) / (h * h);

  return d2Y;
}

f64 integral_by_3_rank_gauss_method(f64 (*func)(f64), f64 a, f64 b, i32 m) noexcept {
  const f64 step = (b - a) / m, step_half = step / 2;

  f64 x0 = a + step_half;
  f64 x1 = x0 - step_half * 0.7745966692;
  f64 x2 = x0 + step_half * 0.7745966692;

  f64 s = 0;

  for (i32 i = 0; i < m; i++) {
    s += 5 / 9.0 * (*func)(x1) + 8 / 9.0 * (*func)(x0) + 5 / 9.0 * (*func)(x2);
    x0 += step;
    x1 = x0 - step_half * 0.7745966692;
    x2 = x0 + step_half * 0.7745966692;
  }

  return step_half * s;
}

std::tuple<f64, i32> get_h() {
  i32 r;
  f64 h{};

  std::cout << "Choose the step:\n"
            << "1. h = 0.2\n"
            << "2. h = 0.1\n"
            << "3. h = 0.05\n";
  std::cin >> r;

  switch (r) {
    case 1:
      h = 0.2;
      break;
    case 2:
      h = 0.1;
      break;
    case 3:
      h = 0.05;
      break;
    default:
      std::cerr << "Vibrano ne dopustimoe znachenie h" << std::endl;
      return std::make_tuple(0.0, EXIT_FAILURE);
  }

  return std::make_tuple(h, EXIT_SUCCESS);
}

std::tuple<i32, i32> get_m() {
  i32 v, m{};
  std::cout << "Choose m:\n1. m=10\n2. m=20\n3. m=40\n";
  std::cin >> v;

  switch (v) {
    case 1:
      m = 10;
      break;
    case 2:
      m = 20;
      break;
    case 3:
      m = 40;
      break;
    default:
      std::cerr << "Vibrano ne dopustimoe zna4enie m" << std::endl;
      return std::make_tuple(0, EXIT_FAILURE);
  }

  return std::make_tuple(m, EXIT_SUCCESS);
}

f64 get_values_distance(f64 left, f64 right) noexcept { return std::fabs(left - right); }

i32 main() {
  i32 a, b;

  std::cout << "a = ";
  std::cin >> a;
  std::cout << "b = ";
  std::cin >> b;

  f64 h;
  i32 result_code;

  std::tie(h, result_code) = get_h();
  if (result_code != EXIT_SUCCESS) return result_code;

  i32 m;
  std::tie(m, result_code) = get_m();
  if (result_code != EXIT_SUCCESS) return result_code;

  const usize n = static_cast<usize>((b - a) / h);
  auto X = vec<f64>(n + 1), Y = vec<f64>(n + 1);

  for (usize i = 0; i <= n; i++) {
    X[i] = a + i * h;
    Y[i] = f(X[i]);
  }

  const vec<f64> DY = dY_precise(X);
  const vec<f64> dY = dY_approximate(Y, h);

  const vec<f64> D2Y = d2Y_precise(X);
  const vec<f64> d2Y = d2Y_approximate(Y, h);

  auto diff_dY = vec<f64>(n + 1), diff_d2Y = vec<f64>(n + 1);

  // Разница между точными и аппроксимированными значениями производных.
  for (usize i = 0; i <= n; i++) {
    diff_dY[i] = get_values_distance(dY[i], DY[i]);
    diff_d2Y[i] = get_values_distance(d2Y[i], D2Y[i]);
  }

  std::cout << "X\tY\tdY\tDY\tdiff1\td2Y\tD2Y\tdiff2\n";

  for (usize i = 0; i <= n; i++)
    printf("%2.1f\t%4.3f\t%4.3f\t%4.3f\t%5.4f\t%4.3f\t%4.3f\t%5.4f\n", X[i],
           Y[i], dY[i], DY[i], diff_dY[i], d2Y[i], D2Y[i], diff_d2Y[i]);

  std::cout.precision(15);

  // Интеграл точно.
  const f64 precise_integral_value = integral_precise(a, b);
  std::cout << std::endl
            << "Precise integral = " << precise_integral_value << std::endl;

  // Интеграл аппроксимированно(приближенно).
  const f64 approximate_integral_value =
      integral_by_3_rank_gauss_method(&f, a, b, m);
  std::cout << "Priblizhenno integral = " << approximate_integral_value
            << std::endl;

  // Разница между точными и аппроксимированными значениями интегралов.
  const f64 approximate_precise_intragral_values_distance =
      get_values_distance(approximate_integral_value, precise_integral_value);
  std::cout << "Diff approximate & precise integrals = "
            << approximate_precise_intragral_values_distance << std::endl;

  return 0;
}
