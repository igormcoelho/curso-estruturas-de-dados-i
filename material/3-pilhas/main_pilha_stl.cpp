// SPDX-License-Identifier:  MIT
// Copyright (C) 2023 - Prof. Igor Machado Coelho

#include <stack>
// #include<fmt/core.h>      // inclui fmt::print
// using fmt::print;

int main() {
  // testando std::stack
  {
    // print("Testando std::stack\n");
    std::stack<char> p;
    p.push('A');
    p.push('B');
    // print("{}\n", p.top());  // B
    p.pop();
    // print("{}\n", p.top());  // A
  }

  return 0;
}
