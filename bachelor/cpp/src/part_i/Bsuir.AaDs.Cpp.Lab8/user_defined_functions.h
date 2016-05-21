// Copyright (c) 2015, reginell. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 8: Programming with Functions.

#ifndef BSUIR_AADS_CPP_LAB8_USER_DEFINED_FUNCTIONS_H_
#define BSUIR_AADS_CPP_LAB8_USER_DEFINED_FUNCTIONS_H_

// TODO: Add comments (Doxygen?). But who cares?

namespace functions {

typedef double(*TestedFunction)(double, double, int &);

void PrintFuncValuesTable(double, double, double, double, TestedFunction, char);
double NinePowerX(double, double, int &);
double MultLog9X(double, double, int &);

}  // namespace functions.

#endif // !BSUIR_AADS_CPP_LAB8_USER_DEFINED_FUNCTIONS_H_
