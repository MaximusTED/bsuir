// Copyright (c) 2017, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.

#pragma once

#include <iostream>
#include "portable.h"

class Tablet : public Portable {
 public:
  Tablet() : screen_in_inches_(0) {}
  virtual ~Tablet() {}

  bool operator==(const Tablet &c) const noexcept {
    return Portable::operator==(c) && screen_in_inches_ == c.screen_in_inches_;
  }

  bool operator!=(const Tablet &c) const noexcept { return !(*this == c); }

  virtual std::ostream &write(std::ostream &stream) const {
    return Portable::write(stream)
           << "Screen (in inches): " << screen_in_inches_ << std::endl;
  }

  virtual std::istream &read(std::istream &stream) {
    Portable::read(stream);
    std::cout << "Screen (in inches): ";
    return stream >> screen_in_inches_;
  }

 private:
  float screen_in_inches_;
};
