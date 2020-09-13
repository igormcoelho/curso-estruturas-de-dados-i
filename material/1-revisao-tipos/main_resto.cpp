#include<iostream>

#include "resto.hpp"

int main() {

   auto z1 = Z{.x = 10};

   printf("invocando metodo imprimex()\n");
   z1.imprimex();

   return 0;
}
