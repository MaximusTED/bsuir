// Copyright (c) 2017, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.

#include "menu.h"
#include "sample_stack_application.h"

template <typename TApp>
void RunApp() {
  auto app = SampleStackApplication<TApp>();
  app.Run();
}

int main() {
  Menu<int> menu{"Choose an action, non-int to exit."};
  menu.WithItem(1, RunApp<int>, "int stack")
      .WithItem(2, RunApp<Monoblock>, "monoblock stack")
      .WithItem(3, RunApp<Laptop>, "laptop stack")
      .WithItem(4, RunApp<Tablet>, "tablet stack");  //-V112

  menu.Run();

  return 0;
}