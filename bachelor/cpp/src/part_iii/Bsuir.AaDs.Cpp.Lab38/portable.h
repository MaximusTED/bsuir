// Copyright (c) 2017, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.

#pragma once

#include <iostream>
#include "computer.h"

class Portable : public Computer {
 public:
  Portable() : weight_(0) {}
  virtual ~Portable() {}

  bool operator==(const Portable &c) const noexcept {
    return Computer::operator==(c) && weight_ == c.weight_;
  }

  bool operator!=(const Portable &c) const noexcept { return !(*this == c); }

  virtual std::ostream &write(std::ostream &stream) const {
    return Computer::write(stream)
           << "Weight (in kg): " << weight_ << std::endl;
  }

  virtual std::istream &read(std::istream &stream) {
    Computer::read(stream);
    std::cout << "Weight (in kg): ";
    return stream >> weight_;
  }

 protected:
  float weight_;
};
