#ifndef RESTO_HPP
#define RESTO_HPP

#include <fmt/core.h>
//
using fmt::print;

class Z {
 public:
  int x;
  // imprime campo x
  void imprimex() { print("{}\n", this->x); }
};

template <typename Agregado>
concept TemImprimeX = requires(Agregado a) {
  { a.imprimex() };
};

// verifica tipo Z com conceito TemImprimeX
static_assert(TemImprimeX<Z>);

#endif /* RESTO_HPP */
