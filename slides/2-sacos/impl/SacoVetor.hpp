#ifndef SACO_VETOR_HPP
#define SACO_VETOR_HPP

#include "SacoTAD.hpp" // para 'static_assert'

class IteradorVetor1
{
public:
   char *elemento;  // elemento atual
   char *sentinela; // elemento sentinela "final"
   char atual();    // inglês 'current'
   bool terminou(); // inglês 'isDone'
   void proximo();  // inglês 'next'

   // range-based loop (requer *, != and ++)
   char operator*()
   {
      return atual();
   }
   //
   bool operator!=(const IteradorVetor1 &other)
   {
      return elemento != other.elemento;
   }
   //
   void operator++()
   {
      proximo();
   }
};

char IteradorVetor1::atual()
{
   return *this->elemento;
}

bool IteradorVetor1::terminou()
{
   return this->elemento == this->sentinela;
}

void IteradorVetor1::proximo()
{
   this->elemento++;
}

// verifica se agregado IteradorNoEnc1 satisfaz conceito IteradorTAD
static_assert(IteradorTAD<IteradorVetor1>);

constexpr int MAX_N = 5;
class SacoVetor1
{
public:
   typedef char Tipo;
   typedef IteradorVetor1 ItTipo;
   //
   Tipo elementos[MAX_N]; // elementos
   int N;                 // num. de elementos na lista
   void cria();           // inicializa agregado
   void libera();         // finaliza agregado
   void adiciona(Tipo dado);
   ItTipo itera();
   ItTipo busca(Tipo dado);
   void remove(ItTipo it);

   // range-based loop
   ItTipo begin()
   {
      return itera();
   }
   // sentinela marcador de fim
   ItTipo end()
   {
      return IteradorVetor1{.elemento = elementos + N};
   }
};

void SacoVetor1::cria()
{
   this->N = 0;
}

void SacoVetor1::libera()
{
   this->N = 0;
}

void SacoVetor1::adiciona(char dado)
{
   this->elementos[N] = dado;
   this->N++; // N = N + 1
}

IteradorVetor1 SacoVetor1::itera()
{
   IteradorVetor1 it{
       .elemento = this->elementos,
       .sentinela = this->elementos + N};
   return it;
}

IteradorVetor1 SacoVetor1::busca(char dado)
{
   auto it = this->itera();
   while (!it.terminou())
   {
      if (it.atual() == dado)
         return it;
      it.proximo();
   }
   return it;
}

void SacoVetor1::remove(IteradorVetor1 it)
{
   auto *i = it.elemento;
   while (i != (this->elementos + N))
   {
      (*i) = *(i + 1);
      i++;
   }
   this->N--; // N = N - 1
}

IteradorVetor1 buscarec(IteradorVetor1 it, char dado)
{
   if (it.atual() == dado)
      return it;
   else
   {
      it.proximo();
      return buscarec(it, dado);
   }
}

//
// verifica se agregado SacoVetor1 satisfaz conceito SacoTAD
static_assert(SacoTAD<SacoVetor1>);

#endif //SACO_VETOR_HPP