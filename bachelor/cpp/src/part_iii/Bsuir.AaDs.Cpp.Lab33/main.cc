// Copyright (c) 2017, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.

#include <algorithm>
#include <cstring>
#include <iostream>
#include <optional>  // C++17

class String {
  friend std::ostream& operator<<(std::ostream& stream, const String& string);
  friend void swap(String& l, String& r) noexcept;

 public:
  explicit String(std::size_t size) : data_{new char[size + 1]}, size_{size + 1} {}
  explicit String(const char* s = "") : String{strlen(s)} {
    strcpy(data_, s);
  }

  String(const String& string) : String{string.data_} {}
  String(String&& string) noexcept : data_{string.data_}, size_{string.size_} {
    string.data_ = nullptr;
    string.size_ = 0;
  }

  String& operator=(String&& string) noexcept {
    swap(*this, string);
    return *this;
  }
  String& operator=(const String& string) {
    String tmp{string};
    swap(*this, tmp);
    return *this;
  }

  ~String() noexcept {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
  }

  const char* c_str() const noexcept { return data_; }
  // strlen equivalent.
  std::size_t size() const noexcept { return size_ - 1; }

  String operator+(const String& ob) const {
    String obj{size_ + ob.size_ + 1};
    strcpy(obj.data_, data_);
    strcat(obj.data_, ob.data_);
    return obj;
  }
  String& operator+=(const String& string) { return *this = *this + string; }

  bool operator<=(const String& s) const noexcept { return s.size_ <= size_; }
  bool operator>=(const String& s) const noexcept { return s.size_ >= size_; }

  const std::optional<char> operator[](const size_t i) const noexcept {
    return i < size_ ? std::optional<char>(data_[i])
                     : std::optional<char>(std::nullopt);
  }

 private:
  char* data_;
  std::size_t size_;
};

std::ostream& operator<<(std::ostream& stream, const String& string) {
  return stream << string.data_;
}

inline void swap(String& l, String& r) noexcept {
  std::swap(l.data_, r.data_);
  std::swap(l.size_, r.size_);
}

int main() {
  constexpr char first_line[]{"Line 1; "};
  constexpr char second_line[]{"Line 2; "};

  String first{first_line};
  std::cout << "First line: " << first << std::endl;

  String second{second_line};
  std::cout << "Second line: " << second.c_str() << std::endl;

  String third{second + first};
  std::cout << "Second line + First line: " << third << std::endl;

  String fourth;
  fourth = third;
  std::cout << "Third line = Second line + First line: " << fourth << std::endl;

  String fifth;
  fifth += third;

  std::cout << std::endl;
  std::cout << first << (first <= second ? " <= " : " > ") << second
            << std::endl;
  std::cout << fifth << (fifth >= third ? " >= " : " < ") << third << std::endl;
  std::cout << std::endl;

  String sixth{first_line};
  std::cout << "Character at zero-based index " << 5 << " of \"" << sixth
            << "\" with length " << sixth.size() << " is '"
            << sixth[5].value_or('?') << "'" << std::endl;

  return 0;
}
