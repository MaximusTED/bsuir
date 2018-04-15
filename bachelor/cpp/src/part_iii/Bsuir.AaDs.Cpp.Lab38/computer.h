// Copyright (c) 2017, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.

#ifndef COMPUTER_H_
#define COMPUTER_H_

#include <iostream>

class Computer {
  friend std::ostream &operator<<(std::ostream &stream, const Computer &obj);
  friend std::istream &operator>>(std::istream &stream, Computer &obj);

 public:
  Computer() = default;
  virtual ~Computer() = default;

  bool operator==(const Computer &c) const noexcept { return year_ == c.year_; }
  bool operator!=(const Computer &c) const noexcept { return !(*this == c); }

  virtual std::ostream &write(std::ostream &stream) const {
    return stream << "Model (year): " << year_ << std::endl;
  }

  virtual std::istream &read(std::istream &stream) {
    std::cout << "Model (year): ";
    return stream >> year_;
  }

 protected:
  int year_;
};

std::ostream &operator<<(std::ostream &stream, const Computer &obj) {
  return obj.write(stream);
}

std::istream &operator>>(std::istream &stream, Computer &obj) {
  return obj.read(stream);
}

#endif  // !COMPUTER_H_
