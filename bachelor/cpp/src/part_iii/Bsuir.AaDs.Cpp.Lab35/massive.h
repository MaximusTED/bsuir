// Copyright (c) 2017, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.

#ifndef BSUIR_AADS_CPP_LAB35_MASSIVE_H_
#define BSUIR_AADS_CPP_LAB35_MASSIVE_H_

#include <algorithm>  // std::swap
#include <cstddef>    // std::size_t
#include <iostream>   // std::istream, std::ostream

template <class T = std::size_t>
class massive {
  template <class U>
  friend std::istream& operator>>(std::istream& stream, massive<U>& massive);

  template <class U>
  friend std::ostream& operator<<(std::ostream& stream,
                                  const massive<U>& massive);

  template <class U>
  friend void swap(massive<U>& l, massive<U>& r) noexcept;

 public:
  using value_type = T;

  massive(std::size_t n = 0) : n_{n}, mm_{new T*[n]} {
    for (std::size_t i{0}; i < n_; i++) {
      mm_[i] = new T[n];

      for (std::size_t j{0}; j < n_; j++) {
        mm_[i][j] = T{};
      }
    }
  }

  massive(const massive& ob) : massive{ob.n_} {
    for (std::size_t i{0}; i < n_; i++) {
      for (std::size_t j{0}; j < n_; j++) {
        mm_[i][j] = ob.mm_[i][j];
      }
    }
  }

  massive& operator=(massive ob);
  massive operator*(const massive& ob) const;

  ~massive() {
    for (std::size_t i{0}; i < n_; i++) delete[] mm_[i];

    delete[] mm_;
    n_ = 0;
  }

 private:
  std::size_t n_;
  T** mm_;
};

template <class U>
std::istream& operator>>(std::istream& stream, massive<U>& massive) {
  for (std::size_t i{0}; i < massive.n_; i++)
    for (std::size_t j{0}; j < massive.n_; j++)
      if (!(stream >> massive.mm_[i][j])) {
        break;
      }

  return stream;
}

template <class U>
std::ostream& operator<<(std::ostream& stream, const massive<U>& massive) {
  for (std::size_t i{0}; i < massive.n_; i++) {
    for (std::size_t j{0}; j < massive.n_; j++)
      stream << std::setw(3) << massive.mm_[i][j];

    stream << std::endl;
  }
  return stream;
}

template <class U>
inline void swap(massive<U>& l, massive<U>& r) noexcept {
  std::swap(l.mm_, r.mm_);
  std::swap(l.n_, r.n_);
}

template <class T>
massive<T> massive<T>::operator*(const massive& ob) const {
  massive ob1(n_);

  for (std::size_t i{0}; i < n_; i++)
    for (std::size_t k{0}; k < n_; k++) {
      T sum{};

      for (std::size_t j{0}; j < n_; j++) sum += mm_[i][j] * ob.mm_[j][k];

      ob1.mm_[i][k] = sum;
    }

  return ob1;
}

template <class T>
inline massive<T>& massive<T>::operator=(massive ob) {
  swap(*this, ob);
  return *this;
}

#endif  // !BSUIR_AADS_CPP_LAB35_MASSIVE_H_
