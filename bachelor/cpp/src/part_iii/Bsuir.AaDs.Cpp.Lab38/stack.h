#pragma once

#include <iostream>
#include <functional>
#include <iostream>

template<class T>
struct item {
  item(T the_i, item *the_next)
    : i(the_i), next(the_next) {
  }

  T    i;
  item *next;
};

template<class T>
class stack {
  template<class U>
  friend std::ostream& operator <<(std::ostream& stream, const stack<U>& stack);

public:
  stack();
  stack(const stack& s) : stack() {
    //head = NULL;
    item<T>* copy_head = s.head;
    while (copy_head != NULL) {
      push(copy_head->i);
      copy_head = copy_head->next;
    }
  }
  stack& operator =(const stack& s) {
    if (this != &s) //проверка
    {
      this->~stack(); //уничтожение себя
      this->stack::stack(s); // присваивание в себя s
    }
    return *this;
  }

  ~stack();

  void push(T value);
  T pop();

  bool empty() const;
  stack find(std::function<bool(const T&)> criteria) const;

private:
  item<T> *head;
};

template<class T>
stack<T>::stack() : head() {
}

template<class T>
stack<T>::~stack() {
  while (head != NULL) {
    item<T> *p = head->next;
    delete head;
    head = p;
  }
}

template<class T>
void stack<T>::push(T value) {
  head = new item<T>(value, head);
}

template<class T>
T stack<T>::pop() {
  if (head == NULL) {
    std::cerr << "(stack is empty)" << std::endl;
    return T();
  }

  item<T> *p = head;
  head = head->next;
  T it = p->i;
  delete p;

  return it;
}

template<class T>
bool stack<T>::empty() const {
  return head == NULL;
}

template<class T>
stack<T> stack<T>::find(std::function<bool(const T&)> criteria) const {
  stack<T> r;
  item<T> *p = head;
  while (p != NULL) {
    const T i = p->i;
    //это функция, которая определяет, подходит ли данный элемент в условия поиска
    //в criteria функтор equals, вызывается его метод equals.operator ()
    if (criteria(i) == true) {
      r.push(i);
    }

    p = p->next;
  }

  return r;
}

template<class U>
std::ostream& operator <<(std::ostream& stream, const stack<U>& stack) {
  if (stack.head == NULL) {
    stream << "(stack is empty)" << std::endl;
    return stream;
  }

  item<U> *p = stack.head;
  while (p != NULL) {
    stream << p->i << std::endl;
    p = p->next;
  }

  return stream;
}
