// Copyright (c) 2016, reginell. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 2.4: Derivative / integral functions approximation.

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

double f(double x) {
  return pow(x, 2) + 5 * cos(x);
}

std::vector<double> dY_precise(const std::vector<double>& X) {
  const std::size_t n = X.size();
  std::vector<double> DY = std::vector<double>(n);

  // Точное значение 1 производной.
  for (std::size_t i = 0; i < n; i++)
    DY[i] = 2 * X[i] - 5 * sin(X[i]);

  return DY;
}

std::vector<double> d2Y_precise(const std::vector<double>& X) {
  const std::size_t n = X.size();
  std::vector<double> D2Y = std::vector<double>(n);

  // Точное значение 2 производной.
  for (std::size_t i = 0; i < n; i++)
    D2Y[i] = 2 - 5 * cos(X[i]);

  return D2Y;
}

double integral_precise(double x) {
  return pow(x, 3) / 3 + 5 * sin(x);
}

double integral_precise(double a, double b) {
  return integral_precise(b) - integral_precise(a);
}

std::vector<double> dY_approximate(const std::vector<double>& Y, double h) {
  const std::size_t n = Y.size();
  std::vector<double> dY = std::vector<double>(n);

  // Аппроксимация первой производной в крайних точках.
  dY[0] = -(3 * Y[0] - 4 * Y[1] + Y[2]) / (2 * h);
  dY[n - 1] = (Y[n - 3] - 4 * Y[n - 2] + 3 * Y[n - 1]) / (2 * h);

  // Аппроксимация первой производной в остальных точках.
  for (std::size_t i = 1; i < n - 1; i++)
    dY[i] = (Y[i + 1] - Y[i - 1]) / (2 * h);

  return dY;
}

std::vector<double> d2Y_approximate(const std::vector<double>& Y, double h) {
  const std::size_t n = Y.size();
  std::vector<double> d2Y = std::vector<double>(n);

  // В крайних точках не считаем.
  d2Y[0] = d2Y[n - 1] = nan("");

  // Аппроксимация второй производной.
  for (std::size_t i = 1; i < n - 1; i++)
    d2Y[i] = (Y[i - 1] - 2 * Y[i] + Y[i + 1]) / (h * h);

  return d2Y;
}

double integral_by_3_rank_gauss_method(double (*func)(double),
  double a, double b, int m) {
  double step = (b - a) / m, step_half = step / 2;

  double x0 = a + step_half;
  double x1 = x0 - step_half * 0.7745966692;
  double x2 = x0 + step_half * 0.7745966692;

  double s = 0;

  for (int i = 0; i < m; i++) {
    s += 5 / 9.0 * (*func)(x1) + 8 / 9.0 * (*func)(x0) + 5 / 9.0 * (*func)(x2);
    x0 += step;
    x1 = x0 - step_half * 0.7745966692;
    x2 = x0 + step_half * 0.7745966692;
  }

  return step_half * s;
}

int get_h(double &h) {
  int r;

  std::cout << "Vibirete shag:\n"
            << "1 h = 0.2\n" << "2 h = 0.1\n" << "3 h = 0.05\n";
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
    std::cerr << "Vibrano ne dopustimoe zna4enie h" << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int get_m(int &m) {
  int v;
  std::cout << "Viberete m:\n1 m=10\n2 m=20\n3 m=40\n";
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
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

double get_diff(double left, double right) {
  return fabs(fabs(left) - fabs(right));
}

int main() {
  int a, b;

  std::cout << "a = ";
  std::cin >> a;

  std::cout << "b = ";
  std::cin >> b;

  double h;
  int result_code = get_h(h);
  if (result_code != EXIT_SUCCESS) return result_code;

  int m;
  result_code = get_m(m);
  if (result_code != EXIT_SUCCESS) return result_code;

  std::size_t n = static_cast<std::size_t>((b - a) / h);
  std::vector<double> X = std::vector<double>(n + 1),
                      Y = std::vector<double>(n + 1);

  for (std::size_t i = 0; i <= n; i++) {
    X[i] = a + i * h;
    Y[i] = f(X[i]);
  }

  std::vector<double> DY = dY_precise(X);
  std::vector<double> dY = dY_approximate(Y, h);

  std::vector<double> D2Y = d2Y_precise(X);
  std::vector<double> d2Y = d2Y_approximate(Y, h);

  std::vector<double> diff_dY = std::vector<double>(n + 1),
                      diff_d2Y = std::vector<double>(n + 1);

  // Разница между точными и аппроксимированными значениями производных.
  for (std::size_t i = 0; i <= n; i++) {
    diff_dY[i] = get_diff(dY[i], DY[i]);
    diff_d2Y[i] = get_diff(d2Y[i], D2Y[i]);
  }

  std::cout << "X\tY\tdY\tDY\tdiff1\td2Y\tD2Y\tdiff2\n";
  
  for (std::size_t i = 0; i <= n; i++)
    printf("%2.1f\t%4.3f\t%4.3f\t%4.3f\t%5.4f\t%4.3f\t%4.3f\t%5.4f\n",
      X[i], Y[i], dY[i], DY[i], diff_dY[i], d2Y[i], D2Y[i], diff_d2Y[i]);

  // Интеграл точно.
  double Ip = integral_precise(a, b);
  std::cout << std::endl << "Precise integral = " << Ip << std::endl;

  // Интеграл аппроксимированно.
  double Ia = integral_by_3_rank_gauss_method(&f, a, b, m);
  std::cout << "Approximate integral = " << Ia << std::endl;

  // Разница между точными и аппроксимированными значениями интегралов.
  double diffI = get_diff(Ia, Ip);
  std::cout << "Diff approximate & precise integrals = " << diffI << std::endl;

  return 0;
}