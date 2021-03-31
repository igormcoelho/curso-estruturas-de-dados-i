#ifndef LISTAENCADEADA_HPP
#define LISTAENCADEADA_HPP

#include "SacoTAD.hpp" // para 'static_assert'

class NoEnc1
{
public:
   char dado;
   NoEnc1 *proximo;
};

class IteradorNoEnc1
{
public:
   NoEnc1 *no;      // no atual
   char atual();    // inglês 'current'
   bool terminou(); // inglês 'isDone'
   void proximo();  // inglês 'next'

   // range-based loop (requer *, != and ++)
   char operator*()
   {
      return atual();
   }
   //
   bool operator!=(const IteradorNoEnc1 &other)
   {
      return no != other.no;
   }
   //
   void operator++()
   {
      proximo();
   }
};

char IteradorNoEnc1::atual()
{
   return this->no->dado;
}

bool IteradorNoEnc1::terminou()
{
   return this->no == 0;
}

void IteradorNoEnc1::proximo()
{
   this->no = this->no->proximo;
}

// verifica se agregado IteradorNoEnc1 satisfaz conceito IteradorTAD
static_assert(IteradorTAD<IteradorNoEnc1>);

class ListaEnc1
{
public:
   typedef char Tipo;
   typedef IteradorNoEnc1 ItTipo;
   //
   NoEnc1 *inicio; // inicio da lista
   int N;          // num. de elementos na lista
   void cria();    // inicializa agregado
   void libera();  // finaliza agregado
   void adiciona(Tipo dado);
   ItTipo itera();
   ItTipo busca(char dado);
   void remove(ItTipo it);

   // range-based loop
   ItTipo begin()
   {
      return itera();
   }
   //
   ItTipo end()
   {
      return IteradorNoEnc1{.no = 0};
   }
};

void ListaEnc1::cria()
{
   this->N = 0;
   this->inicio = 0;
}

void ListaEnc1::libera()
{
   while (this->inicio != 0)
   {
      auto *prox = this->inicio->proximo;
      delete this->inicio;
      this->inicio = prox;
   }
   this->N = 0;
}

void ListaEnc1::adiciona(char dado)
{
   auto *no = new NoEnc1{.dado = dado, .proximo = inicio};
   this->inicio = no;
   this->N++; // N = N + 1
}

IteradorNoEnc1 ListaEnc1::itera()
{
   IteradorNoEnc1 it{.no = this->inicio};
   return it;
}

IteradorNoEnc1 ListaEnc1::busca(char dado)
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

void ListaEnc1::remove(IteradorNoEnc1 it)
{
   auto *prox = it.no->proximo;
   (*it.no) = (*it.no->proximo); // sobrescrita
   delete prox;
   this->N--; // N = N - 1
}

IteradorNoEnc1 buscarec(IteradorNoEnc1 it, char dado)
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
// verifica se agregado ListaEnc1 satisfaz conceito SacoTAD
static_assert(SacoTAD<ListaEnc1>);

#endif //LISTAENCADEADA_HPP