// Copyright (c) 2017, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.

#ifndef MENU_H_
#define MENU_H_

#include <functional>
#include <iostream>
#include <map>

template <typename TKey>
class Menu {
 public:
  using key_type = TKey;
  using action_type = std::function<void(void)>;

  Menu(const std::string& prompt) : prompt_{prompt}, item_actions_{} {}
  Menu& WithItem(const key_type& key, action_type action,
                 const std::string& description) {
    const auto result = item_actions_.insert(
        std::pair<key_type, ActionDescriptor>(key, {action, description}));

    if (!result.second) {
      throw std::exception("Item with this key was already added.");
    }

    return *this;
  }

  void Run() {
    key_type key;
    std::map<key_type, ActionDescriptor>::iterator it;

    do {
      ClearScreen();
      PrintActions();

      if (!(std::cin >> key)) {
        // Clear bad bits to allow work with cin later.
        std::cin.clear();
        std::cin.ignore();
        break;
      }

      if ((it = item_actions_.find(key)) == item_actions_.end()) {
        std::cerr << "Unexpected key, use allowed one." << std::endl;
        WaitForInput();
        continue;
      }

      it->second.action_();
    } while (true);
  }

 private:
  struct ActionDescriptor {
    ActionDescriptor(action_type action, const std::string& description)
        : action_{action}, description_{description} {}

    action_type action_;
    std::string description_;
  };

  const std::string prompt_;
  std::map<key_type, ActionDescriptor> item_actions_;

  void WaitForInput() const { system("pause"); }
  void ClearScreen() const { system("cls"); }
  void PrintActions() const {
    if (prompt_.length() > 0) std::cout << prompt_.c_str() << std::endl;

    for (auto&& pair : item_actions_) {
      std::cout << pair.first << " - " << pair.second.description_.c_str()
                << std::endl;
    }
  }

  Menu(const Menu& m) = delete;
  Menu& operator=(const Menu& m) = delete;
};

#endif  // !MENU_H_
