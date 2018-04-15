// Copyright (c) 2017, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.

#ifndef DESKTOP_H_
#define DESKTOP_H_

#include <iostream>
#include "computer.h"

class Desktop : public Computer {
 public:
  Desktop() = default;
  virtual ~Desktop() = default;

  bool operator==(const Desktop &c) const noexcept {
    return Computer::operator==(c) && noise_level_ == c.noise_level_;
  }

  bool operator!=(const Desktop &c) const noexcept { return !(*this == c); }

  std::ostream &write(std::ostream &stream) const override {
    return Computer::write(stream)
           << "Noise (in db): " << noise_level_ << std::endl;
  }

  std::istream &read(std::istream &stream) override {
    Computer::read(stream);
    std::cout << "Noise (in db): ";
    return stream >> noise_level_;
  }

 protected:
  float noise_level_;
};

#endif  // !DESKTOP_H_
