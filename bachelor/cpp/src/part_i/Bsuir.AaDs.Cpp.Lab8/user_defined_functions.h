// Copyright (c) 2015, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.
//
// Subject: Algorithms and Data structures (AaDs).
// Lab work 8: Programming with Functions.

#ifndef BSUIR_AADS_CPP_LAB8_USER_DEFINED_FUNCTIONS_H_
#define BSUIR_AADS_CPP_LAB8_USER_DEFINED_FUNCTIONS_H_

// TODO: Add comments (Doxygen?). But who cares?

namespace functions {

using i32 = int;
using f64 = double;

typedef f64 (*TestedFunction)(f64, f64, i32 &);

void PrintFuncValuesTable(f64, f64, f64, f64, TestedFunction, char);
f64 NinePowerX(f64, f64, i32 &);
f64 MultLog9X(f64, f64, i32 &);

}  // namespace functions.

#endif  // !BSUIR_AADS_CPP_LAB8_USER_DEFINED_FUNCTIONS_H_
