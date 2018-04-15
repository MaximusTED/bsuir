// Copyright (c) 2017, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.

#pragma once

#include <iostream>
#include "desktop.h"

class Monoblock : public Desktop {
 public:
  Monoblock() : screen_size_(0) {}
  virtual ~Monoblock() {}

  bool operator==(const Monoblock &c) const noexcept {
    return Desktop::operator==(c) && screen_size_ == c.screen_size_;
  }

  bool operator!=(const Monoblock &c) const noexcept { return !(*this == c); }

  virtual std::ostream &write(std::ostream &stream) const {
    return Desktop::write(stream)
           << "Sreen (in px): " << screen_size_ << std::endl;
  }

  virtual std::istream &read(std::istream &stream) {
    Desktop::read(stream);
    std::cout << "Sreen (in px): ";
    return stream >> screen_size_;
  }

 private:
  float screen_size_;
};
