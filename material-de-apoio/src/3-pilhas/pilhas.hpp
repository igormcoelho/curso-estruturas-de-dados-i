// SPDX-License-Identifier:  MIT
// Copyright (C) 2023 - Prof. Igor Machado Coelho

#ifndef ED_I_PILHAS_HPP
#define ED_I_PILHAS_HPP

#include <memory>   // para std::unique_ptr
#include <utility>  // para std::move

// atalho de nome: uptr<X> representa std::unique_ptr<X>
template <typename T>
using uptr = std::unique_ptr<T>;

template <typename Agregado, typename Tipo>
concept PilhaTAD = requires(Agregado a, Tipo t) {
  // requer operação 'topo'
  { a.topo() };
  // requer operação 'empilha' sobre tipo 't'
  { a.empilha(t) };
  // requer operação 'desempilha'
  { a.desempilha() };
  // requer operação 'tamanho'
  { a.tamanho() };
};

// ================== Pilha sequencial 1 ===============

constexpr int MAXN = 100'000;  // capacidade máxima da pilha
class PilhaSeq1 {
 public:
  // NOLINTNEXTLINE
  char elementos[MAXN];  // elementos na pilha
  int N;                 // num. de elementos na pilha
  void cria() { this->N = 0; }
  void libera() {
    // nenhum recurso dinâmico para desalocar
  }
  char topo() {
    // NOLINTNEXTLINE
    return this->elementos[this->N - 1];
  }
  void empilha(char dado) {
    // NOLINTNEXTLINE
    this->elementos[this->N] = dado;
    this->N++;  // N = N + 1
  }

  char desempilha() {
    this->N--;  // N = N - 1
    // NOLINTNEXTLINE
    return this->elementos[this->N];
  }
  int tamanho() { return this->N; };
};
// verifica se agregado PilhaSeq1 satisfaz conceito PilhaTAD
static_assert(PilhaTAD<PilhaSeq1, char>);

// ================== Pilha encadeada 1 ===============

class NoPilha1 {
 public:
  char dado;
  NoPilha1* prox;
};

class PilhaEnc1 {
 public:
  NoPilha1* inicio;
  int N;
  void cria() {
    this->N = 0;       // zero elementos na pilha
    this->inicio = 0;  // endereço zero de memória
  }
  void libera() {
    while (this->N > 0) {
      NoPilha1* p = this->inicio->prox;
      delete this->inicio;
      this->inicio = p;
      this->N--;
    }
  }
  char topo() { return this->inicio->dado; }
  void empilha(char v) {
    // NOLINTNEXTLINE
    auto* no = new NoPilha1{.dado = v, .prox = this->inicio};
    this->inicio = no;
    this->N++;  // N = N + 1
  }
  char desempilha() {
    NoPilha1* p = this->inicio->prox;
    char r = this->inicio->dado;
    delete this->inicio;
    this->inicio = p;
    this->N--;  // N=N-1
    return r;
  }
  int tamanho() { return this->N; }
};
// verifica agregado PilhaEnc1
static_assert(PilhaTAD<PilhaEnc1, char>);

// ================== Pilha encadeada 2 ===============

class NoPilha2 {
 public:
  char dado;
  uptr<NoPilha2> prox;
};

class PilhaEnc2 {
 public:
  uptr<NoPilha2> inicio;
  int N;
  void cria() {
    this->N = 0;  // zero elementos na pilha
                  // this->inicio = 0; // não é necessário inicializar
  }
  void libera() {
    // seguro contra stack overflow
    while (this->tamanho() > 0) {
      this->inicio = std::move(this->inicio->prox);
      this->N--;
    }
  }
  char topo() { return this->inicio->dado; }
  void empilha(char v) {
    this->inicio = std::make_unique<NoPilha2>(
        NoPilha2{.dado = v, .prox = std::move(this->inicio)});
    this->N++;  // N = N + 1
  }
  char desempilha() {
    char r = this->inicio->dado;
    this->inicio = std::move(this->inicio->prox);
    this->N--;  // N=N-1
    return r;
  }
  int tamanho() { return this->N; }
};
// verifica agregado PilhaEnc2
static_assert(PilhaTAD<PilhaEnc2, char>);

#endif  // ED_I_PILHAS_HPP
