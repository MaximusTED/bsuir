// Copyright (c) 2017, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.

#pragma once

#include <iostream>
#include "laptop.h"
#include "menu.h"
#include "monoblock.h"
#include "stack.h"
#include "tablet.h"

template <class TKey>
class SampleStackApplication {
 public:
  virtual void Run();

 private:
  stack<TKey> stack_;
};

template <class TKey>
void SampleStackApplication<TKey>::Run() {
  Menu<int> menu{"Choose action, non-int to exit to main menu:"};
  menu.WithItem(1,
                [&] {
                  TKey value;
                  std::cout << "> ";
                  std::cin >> value;
                  stack_.push(value);
                },
                "Add one")
      .WithItem(2,
                [&] {
                  std::cout << stack_ << std::endl;
                  system("pause");
                },
                "Show all")
      .WithItem(3,
                [&] {
                  std::cout << "> ";

                  const auto item = stack_.pop();

                  if (item.has_value()) {
                    std::cout << item.value() << std::endl;
                  }

                  system("pause");
                },
                "Remove & show one")
      .WithItem(4,  //-V112
                [&] {
                  while (!stack_.empty()) stack_.pop();
                },
                "Remove all")
      .WithItem(5,
                [&] {
                  std::cout << "Enter item to find:" << std::endl;

                  TKey item;
                  std::cin >> item;

                  const stack<TKey> found_items =
                      stack_.find([&](auto key) { return key == item; });

                  if (!found_items.empty()) {
                    std::cout << "Stack of found items:" << std::endl
                              << found_items;
                  } else {
                    std::cout << "No items as the following one are found:"
                              << std::endl
                              << item << std::endl;
                  }

                  system("pause");
                },
                "Find item");

  menu.Run();
}
