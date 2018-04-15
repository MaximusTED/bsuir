// Copyright (c) 2017, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.

#pragma once

#include <functional>
#include <iostream>
#include <optional>  // C++17

template <class TKey>
struct item {
  item(TKey the_i, item* the_next) : i(the_i), next(the_next) {}

  const TKey i;
  item* next;
};

template <class TKey>
class stack {
  template <class U>
  friend std::ostream& operator<<(std::ostream& stream, const stack<U>& stack);

 public:
  stack();
  stack(const stack& s) : stack{} {
    item<TKey>* copy_head = s.head;
    while (copy_head != nullptr) {
      push(copy_head->i);
      copy_head = copy_head->next;
    }
  }
  stack& operator=(const stack& s) {
    if (this != &s) {
      this->~stack();
      this->stack::stack(s);
    }
    return *this;
  }

  ~stack();

  void push(TKey value);
  std::optional<TKey> pop();

  bool empty() const;
  stack find(std::function<bool(const TKey&)> criteria) const;

 private:
  item<TKey>* head;
};

template <class TKey>
stack<TKey>::stack() : head() {}

template <class TKey>
stack<TKey>::~stack() {
  while (pop().has_value()) {
  }
}

template <class TKey>
void stack<TKey>::push(TKey value) {
  head = new item<TKey>(value, head);
}

template <class TKey>
std::optional<TKey> stack<TKey>::pop() {
  if (head == nullptr) {
    return {};
  }

  item<TKey>* p = head;
  head = head->next;
  TKey it = p->i;
  delete p;

  return it;
}

template <class TKey>
bool stack<TKey>::empty() const {
  return head == nullptr;
}

template <class TKey>
stack<TKey> stack<TKey>::find(std::function<bool(const TKey&)> criteria) const {
  stack<TKey> items;
  item<TKey>* p = head;

  while (p != nullptr) {
    const TKey i = p->i;

    if (criteria(i)) items.push(i);

    p = p->next;
  }

  return items;
}

template <class U>
std::ostream& operator<<(std::ostream& stream, const stack<U>& stack) {
  if (stack.head == nullptr) {
    stream << "(stack is empty)" << std::endl;
    return stream;
  }

  item<U>* p = stack.head;
  while (p != nullptr) {
    stream << p->i << std::endl;
    p = p->next;
  }

  return stream;
}
