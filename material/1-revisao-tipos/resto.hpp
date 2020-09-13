#ifndef RESTO_HPP
#define RESTO_HPP

#include<iostream>

class Z
{
public:
   int x;
   // imprime campo x
   void imprimex() {
      printf("%d\n", this->x);
   }
};

template<typename Agregado>
concept bool
TemImprimeX = requires(Agregado a) {
   {
      a.imprimex()
   }
};

// verifica tipo Z com conceito TemImprimeX
static_assert(TemImprimeX<Z>);


#endif /* RESTO_HPP */
