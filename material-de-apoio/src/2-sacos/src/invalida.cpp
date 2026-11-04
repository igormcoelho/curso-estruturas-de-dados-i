// Invalidação de iterador: o Clang 23 detecta no std::vector, NÃO num saco próprio.
// (Testado. Mesmo resultado sem anotações, com LFTM e com gsl::Owner/Pointer.)
// Compilar (Clang 23):
//   clang++-23 -std=c++20 -fsyntax-only -Wlifetime-safety \
//     -Wlifetime-safety-permissive -Wlifetime-safety-invalidation invalida.cpp
// Resultado: A, B, C e controle em silêncio; D e D' avisam, com 3 notas: onde nasce
// a dependência, onde o vetor é invalidado (push_back) e onde é usado depois.
// Três sacos iguais, mudando só as anotações:
//   A: nenhuma anotação
//   B: iterador() anotado com LFTM (iterador depende do saco)
//   C: B + [[gsl::Owner]] no saco e [[gsl::Pointer]] no iterador
// Em cada caso: cria iterador, chama adiciona() (não-const), usa o iterador.
// Controle: tamanho() é const e não invalida (também sem aviso, como esperado).
#include <cstdio>
#include <vector>

#if defined(__has_cpp_attribute) && __has_cpp_attribute(clang::lifetimebound)
#define LFTM [[clang::lifetimebound]]
#else
#define LFTM
#endif

struct ItA { const char* atual; char le() const { return *atual; } };
struct SacoA {
   char e[10]; int N = 0;
   ItA  iterador()           { return {e}; }
   void adiciona(char x)     { e[N++] = x; }
   int  tamanho() const      { return N; }
};

struct ItB { const char* atual; char le() const { return *atual; } };
struct SacoB {
   char e[10]; int N = 0;
   ItB  iterador() LFTM      { return {e}; }
   void adiciona(char x)     { e[N++] = x; }
   int  tamanho() const      { return N; }
};

struct [[gsl::Pointer(char)]] ItC { const char* atual; char le() const { return *atual; } };
struct [[gsl::Owner(char)]] SacoC {
   char e[10]; int N = 0;
   ItC  iterador() LFTM      { return {e}; }
   void adiciona(char x)     { e[N++] = x; }
   int  tamanho() const      { return N; }
};

int main() {
   SacoA a; a.adiciona('a');
   auto ia = a.iterador(); a.adiciona('b'); std::printf("%c", ia.le()); // A: silêncio

   SacoB b; b.adiciona('a');
   auto ib = b.iterador(); b.adiciona('b'); std::printf("%c", ib.le()); // B: silêncio (LFTM não basta)

   SacoC c; c.adiciona('a');
   auto ic = c.iterador(); c.adiciona('b'); std::printf("%c", ic.le()); // C: silêncio (gsl::Owner/Pointer não bastam)

   auto jc = c.iterador(); c.tamanho();     std::printf("%c", jc.le()); // controle: silêncio

   // D: std::vector — o Clang 23 sabe que push_back invalida ponteiros e iteradores
   std::vector<char> d{'a'};
   const char* pd = &d[0]; d.push_back('b'); std::printf("%c", *pd);   // D: AVISA (ponteiro)
   auto        id = d.begin(); d.push_back('c'); std::printf("%c", *id); // D': AVISA (iterador também)
}

/*
Resumo (ver outros testes main-lifetime-clang23.cpp):

a conclusão é clara: a detecção de invalidação do Clang 23 não se aplica a tipos próprios,
 nem com LFTM e as marcações gsl::Owner/gsl::Pointer. 
 Ela vale só para os contêineres que o compilador já conhece, como o std::vector do T7.

Caso:
- invalidação por método não-const em saco próprio (sem anotação, com LFTM, ou com gsl::Owner/Pointer) => clang23 em silencio

*/