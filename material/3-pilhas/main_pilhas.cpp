// SPDX-License-Identifier:  MIT
// Copyright (C) 2023 - Prof. Igor Machado Coelho

#include <stack>
//
#include <fmt/core.h>  // NOLINT
//

#include "./pilhas.hpp"

using fmt::print;

int main() {
  // testando PilhaSeq1
  {
    print("Testando PilhaSeq1\n");
    PilhaSeq1 p{};
    p.cria();
    p.empilha('A');
    p.empilha('B');
    p.empilha('C');
    print("{}\n", p.topo());
    print("{}\n", p.desempilha());
    p.empilha('D');
    while (p.tamanho() > 0) print("{}\n", p.desempilha());
    p.libera();
  }
  // testando PilhaEnc1
  {
    print("Testando PilhaEnc1\n");
    PilhaEnc1 p{};
    p.cria();
    p.empilha('A');
    p.empilha('B');
    p.empilha('C');
    print("{}\n", p.topo());
    print("{}\n", p.desempilha());
    p.empilha('D');
    while (p.tamanho() > 0) print("{}\n", p.desempilha());
    p.libera();
  }
  // testando PilhaEnc2
  {
    print("Testando PilhaEnc2\n");
    PilhaEnc2 p;
    p.cria();
    p.empilha('A');
    p.empilha('B');
    p.empilha('C');
    print("{}\n", p.topo());
    print("{}\n", p.desempilha());
    p.empilha('D');
    while (p.tamanho() > 0) print("{}\n", p.desempilha());
    p.libera();
  }

  // testando std::stack
  {
    print("Testando std::stack\n");
    std::stack<char> p;
    p.push('A');
    p.push('B');
    print("{}\n", p.top());  // B
    p.pop();
    print("{}\n", p.top());  // A
  }

  return 0;
}
