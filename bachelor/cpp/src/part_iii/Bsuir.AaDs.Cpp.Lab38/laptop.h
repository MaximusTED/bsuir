// Copyright (c) 2017, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.

#pragma once

#include <iostream>
#include "portable.h"

class Laptop : public Portable {
 public:
  Laptop() = default;
  virtual ~Laptop() = default;

  bool operator==(const Laptop &c) const noexcept {
    return Portable::operator==(c) && battery_capacity_ == c.battery_capacity_;
  }

  bool operator!=(const Laptop &c) const noexcept { return !(*this == c); }

  virtual std::ostream &write(std::ostream &stream) const {
    return Portable::write(stream)
           << "Capacity (in h): " << battery_capacity_ << std::endl;
  }

  virtual std::istream &read(std::istream &stream) {
    Portable::read(stream);
    std::cout << "Capacity (in h): ";
    return stream >> battery_capacity_;
  }

 private:
  int battery_capacity_;
};
