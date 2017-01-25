#pragma once

#include <iostream>
#include "sample_stack_application.h"

class StackSamplesApplication {
public:
  StackSamplesApplication() {
  }
  ~StackSamplesApplication() {
  }
  void run();
};

void StackSamplesApplication::run() {
  int ch;

  do {
    system("cls");

    std::cout << "1 - int stack" << std::endl;
    std::cout << "2 - Monoblock stack" << std::endl;
    std::cout << "3 - Laptop stack" << std::endl;
    std::cout << "4 - Tablet stack" << std::endl;
    std::cout << "5 - Return to Desktop" << std::endl;
    std::cout << "Choose an action (1-5): ";

    ISampleStackApplication *app = NULL;

    std::cin >> ch;
    
    switch (ch) {
      case 1:
        app = new SampleStackApplication<int>();
        break;
      case 2:
        app = new SampleStackApplication<Monoblock>();
        break;
      case 3:
        app = new SampleStackApplication<Laptop>();
        break;
      case 4:
        app = new SampleStackApplication<Tablet>();
        break;
    }

    if (app) {
      app->run();
      delete app;
    }    
  } while (ch != 5);
}
