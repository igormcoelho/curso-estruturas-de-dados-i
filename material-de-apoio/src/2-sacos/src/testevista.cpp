// clang++-23 -std=c++20 -fsyntax-only -Wlifetime-safety -Wlifetime-safety-permissive testevista.cpp
//
// Vista dos slides: agregado (A) vs. construtor anotado (B).
//
// Compilar (Clang 23):
//   clang++-23 -std=c++20 -fsyntax-only -Wlifetime-safety \
//     -Wlifetime-safety-permissive testevista.cpp
//
// Esperado: UM aviso, só em B ("local variable 'x' does not live long
// enough" [-Wlifetime-safety-use-after-scope]). A passa em silêncio.
#include <cstdio>

#if defined(__has_cpp_attribute) && __has_cpp_attribute(clang::lifetimebound)
#define LFTM [[clang::lifetimebound]]
#else
#define LFTM
#endif

struct VistaA {                  // A: como nos slides (agregado)
   const int* origem;
   int le() { return *origem; }
};

struct VistaB {                  // B: construtor com ponteiro anotado
   const int* origem;
   VistaB(const int* x LFTM) : origem(x) {}
   int le() { return *origem; }
};

int main() {
   int z = 0;
   VistaA a{.origem = &z};
   { int x = 10; a = VistaA{.origem = &x}; }   // pendente, NÃO detectado
   VistaB b{&z};
   { int x = 10; b = VistaB(&x); }             // pendente, detectado
   std::printf("%d %d\n", a.le(), b.le());
}


