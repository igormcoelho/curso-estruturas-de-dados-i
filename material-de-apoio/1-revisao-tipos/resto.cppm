export module resto;

import std;

export class Z {
 public:
  int x;
  // imprime campo x
  void imprimex() { std::print("{}\n", this->x); }
};

template <typename Agregado>
concept TemImprimeX = requires(Agregado a) {
  { a.imprimex() };
};

// verifica tipo Z com conceito TemImprimeX
static_assert(TemImprimeX<Z>);
