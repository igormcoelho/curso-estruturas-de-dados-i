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

// para construir manualmente:
// g++ --std=c++20 main_pilha_stl.cpp -o appPilhas
//
// para construir com cmake:
// mkdir -p build && cd build && cmake .. && make
//
