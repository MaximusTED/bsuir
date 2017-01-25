#pragma once

#include <iostream>
#include "monoblock.h"
#include "laptop.h"
#include "tablet.h"
#include "equals.h"
#include "stack.h"

class ISampleStackApplication {
public:
  virtual void run() {
  }
  virtual ~ISampleStackApplication() {
  }
};

template <class T>
class SampleStackApplication : public ISampleStackApplication {
public:
  virtual void run();

private:
  stack<T> stack_;
};

template <class T>
void SampleStackApplication<T>::run() {
  int ch;

  do {
    system("cls");
    std::cout << "1 - Add one" << std::endl;
    std::cout << "2 - Show all" << std::endl;
    std::cout << "3 - Remove & show one" << std::endl;
    std::cout << "4 - Remove all" << std::endl;
    std::cout << "5 - Find item" << std::endl;
    std::cout << "6 - Return to main menu" << std::endl;
    std::cout << "(1-6): ";
    
    std::cin >> ch;
    
    switch (ch) {
      case 1: {
        T value;
        std::cout << "> ";
        std::cin >> value;
        stack_.push(value);
        break;
      }
      case 2:
        std::cout << stack_ << std::endl;
        system("pause");
        break;
      case 3: {
        bool canPop = !stack_.empty();

        T value = stack_.pop();
        std::cout << "> ";

        if (canPop) {
          std::cout << value << std::endl;
        }

        system("pause");
        break;
      }
      case 4:
        while (!stack_.empty())
          stack_.pop();
        break;
      case 5:
      {
        std::cout << "Enter item to find:" << std::endl;

        T item;
        std::cin >> item;

        stack<T> found_items = stack_.find(equals<T>(item));

        if (!found_items.empty()) {
          std::cout << "Stack of found items:" << std::endl << found_items;
        } else {
          std::cout << "No items as the following one are found:" << std::endl
                    << item << std::endl;
        }
        
        system("pause");
        break;
      }
    }
  } while (ch != 6);
}
