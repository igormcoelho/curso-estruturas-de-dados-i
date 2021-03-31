#include <iostream>

#include "SacoTAD.hpp"

#include "ListaEncadeada.hpp"
#include "SacoVetor.hpp"

int main()
{
   SacoTAD s = ListaEnc1(); // alguma implementação
   s.cria();
   s.adiciona('c');
   s.adiciona('a');
   s.adiciona('b');
   s.adiciona('a');
   printf("%d\n", s.busca('a').terminou()); // 0
   printf("%d\n", s.busca('d').terminou()); // 1
   printf("N=%d\n", s.N);                   // N=4
   for (auto it = s.itera(); !it.terminou(); it.proximo())
      printf("%c\n", it.atual()); // a b a c
   //
   s.remove(s.busca('b'));
   printf("N=%d\n", s.N); // N=3
   for (auto x : s)
      printf("%c\n", x); // a a c

   s.libera();
   printf("N=%d\n", s.N); // N=0

   printf("    ====VETOR====    \n");

   SacoTAD v = SacoVetor1(); // alguma implementação
   v.cria();
   v.adiciona('c');
   v.adiciona('a');
   v.adiciona('b');
   v.adiciona('a');
   printf("%d\n", v.busca('a').terminou()); // 0
   printf("%d\n", v.busca('d').terminou()); // 1
   printf("N=%d\n", v.N);                   // N=4
   for (auto it = v.itera(); !it.terminou(); it.proximo())
      printf("%c\n", it.atual()); // c a b a
   //
   v.remove(v.busca('b'));
   printf("N=%d\n", v.N); // N=3
   for (auto x : v)
      printf("%c\n", x); // c a a

   v.libera();
   printf("N=%d\n", v.N); // N=0

   return 0;
}
