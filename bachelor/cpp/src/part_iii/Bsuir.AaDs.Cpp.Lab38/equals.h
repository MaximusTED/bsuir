#ifndef EQUALS_H_
#define EQUALS_H_

template<class T>
struct equals {
  const T item_;

  equals(const T& item) : item_(item) {
  }

  bool operator() (const T& p) const noexcept {
    return item_ == p;
  }
};

#endif  // !EQUALS_H_
