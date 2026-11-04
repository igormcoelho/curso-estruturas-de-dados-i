// Testes mínimos de lifetime. Compile UM teste por vez: -DT=1 ... -DT=10 (Clang 18 e 23 testados; Clang 21 não)
#include <string>
#include <string_view>
#include <vector>
#include <cstdio>

#ifndef __has_cpp_attribute
#define LFTM
#elif __has_cpp_attribute(msvc::lifetimebound)
#define LFTM [[msvc::lifetimebound]]
#elif __has_cpp_attribute(clang::lifetimebound)
#define LFTM [[clang::lifetimebound]]
#else
#define LFTM
#endif

#ifndef __has_cpp_attribute
#define LCB(x)
#elif __has_cpp_attribute(clang::lifetime_capture_by)
#define LCB(x) [[clang::lifetime_capture_by(x)]]
#else
#define LCB(x)
#endif

std::string mk() { return "temporario"; }

#if T == 1  // view de local que sai de escopo (sem anotação)
int main() {
std::string_view v;
{ std::string s = "hello"; v = s; }
std::printf("%zu\n", v.size());          // Clang 18: silêncio | Clang 23: avisa (-Wlifetime-safety-use-after-scope)
}
#elif T == 2  // método nomeado com LFTM chamado em temporário
struct S {
std::string s;
const char* c_str() const LFTM { return s.c_str(); }
};
int main() {
const char* p = S{mk()}.c_str();         // Clang 18: avisa (-Wdangling) | Clang 23: -Wdangling + -Wlifetime-safety-use-after-scope
std::printf("%s\n", p);
}
#elif T == 3  // LFTM em PARÂMETRO de construtor: atributo ACEITO e funciona (Clang 18 e 23)
struct View {
const char* p;
View(const std::string& s LFTM) : p(s.c_str()) {}
};
int main() {
View a = mk();                           // copy-init:  Clang 18: -Wdangling | Clang 23: -Wdangling + análise nova
View b{mk()};                            // brace-init: Clang 18: -Wdangling | Clang 23: -Wdangling + análise nova
std::printf("%s %s\n", a.p, b.p);        // Clang 21: não testado (houve relato de erro com o atributo em outra posição?)
}
#elif T == 4  // operador de conversão vs. inicialização (motivo concreto para a C.164)
struct View { const char* p; View(const char* x) : p(x) {} };
struct Str {
std::string s;
operator View() const LFTM { return View{s.c_str()}; }
};
int main() {
View a = Str{mk()};                      // copy-init:  Clang 18: -Wdangling | Clang 23: -Wdangling + análise nova
View b{Str{mk()}};                       // brace-init: Clang 18: SILÊNCIO | Clang 23: só a análise nova (-Wdangling não pega)
std::printf("%s %s\n", a.p, b.p);
}
#elif T == 5  // escape por função: a anotação é OBRIGATÓRIA
std::string_view sem(std::string_view s)      { return s; }
std::string_view com(std::string_view s LFTM) { return s; }
int main() {
auto a = sem(mk());                      // silêncio no Clang 18 e no 23
auto b = com(mk());                      // Clang 18: silêncio | Clang 23: -Wdangling-gsl + -Wlifetime-safety-use-after-scope
std::printf("%zu %zu\n", a.size(), b.size());
}
#elif T == 6  // captura em CAMPO via método, origem TEMPORÁRIA (compare com T9)
struct Cache {
std::string_view k;
void set(std::string_view x LCB(this)) { k = x; }
};
int main() {
Cache c;
c.set(mk());                             // Clang 18: silêncio | Clang 23: avisa (-Wdangling-capture)
std::printf("%zu\n", c.k.size());
}
#elif T == 7  // invalidação de iterador em vector
int main() {
std::vector<int> v{1};
int* p = &v[0];
v.push_back(2);                          // pode realocar
std::printf("%d\n", *p);                 // Clang 18: silêncio | Clang 23: avisa (-Wlifetime-safety-invalidation)
}
#elif T == 8  // a Vista do curso (agregado com ponteiro em campo): NADA verifica
struct VistaInt {
using Tipo = int;
const Tipo* origem;
Tipo le() { return *origem; }
};
int main() {
VistaInt y{};
{ int x = 10; y = VistaInt{.origem = &x}; }
std::printf("%d\n", y.le());             // silêncio no Clang 18 e no 23 (sem construtor para anotar)
}
#elif T == 9  // captura em campo, origem LOCAL morre ao sair do escopo: a lacuna durável
struct Cache {
std::string_view k;
void set(std::string_view x LCB(this)) { k = x; }
};
int main() {
Cache c;
{ std::string s = "local"; c.set(s); }
std::printf("%zu\n", c.k.size());       // silêncio no Clang 18 e no 23, mesmo com LCB
}
#elif T == 10 // Vista do curso COM construtor anotado: passa a ser verificada
struct VistaInt {
const int* origem;
VistaInt(const int& x LFTM) : origem(&x) {}
int le() { return *origem; }
};
int main() {
int z = 0;
VistaInt y{z};
{ int x = 10; y = VistaInt(x); }
std::printf("%d\n", y.le());            // Clang 18: silêncio | Clang 23: avisa (-Wlifetime-safety-use-after-scope)
}
#elif T == 11 // Vista com construtor recebendo PONTEIRO anotado
struct VistaInt {
const int* origem;
VistaInt(const int* x LFTM) : origem(x) {}
int le() { return *origem; }
};
int main() {
int z = 0;
VistaInt y{&z};
{ int x = 10; y = VistaInt(&x); }
std::printf("%d\n", y.le());            // pego no Clang 23?
}
#endif

/*
Resumo dos resultados:

Pego:

- view de local que sai de escopo (T1);
- método nomeado com LFTM chamado em temporário (T2);
- LFTM em parâmetro de construtor, por cópia e por chaves (T3);
- operador de conversão por chaves (T4), só pela análise nova, sem o -Wdangling;
- escape por função, *desde que* o parâmetro esteja anotado (T5);
- captura em campo via método, *quando a origem é temporária* (T6, -Wdangling-capture);
- invalidação por push_back no vector (T7);
- vista com *construtor anotado* cuja origem sai de escopo (T10).

Não pego:

- escape por função sem anotação (T5);
- vista *agregada* com ponteiro em campo, como a VistaInt dos slides (T8);
- captura em campo via método *quando a origem é um local* que morre no fim do escopo (T9).

Resumo Caso a Caso:
T1, T7 e T10 avisam só pela análise nova; 
T2, T3 e o copy-init do T4 avisam por -Wdangling e pela análise nova;
o brace-init do T4 (linha 60) avisa só pela análise nova; 
T5 avisa só na versão anotada (linha 68); 
T6 avisa por -Wdangling-capture; 
T8 e T9 ficam em silêncio.

Resumo Geral: 
A análise do Clang 23 acompanha o tempo de vida *por construção e atribuição de valores anotados*, 
mas não *por escrita em campos de objetos que já existem*. 
Compare T9 com T10: o mesmo tipo de vista, escrito com um construtor anotado, 
passa a ser verificado.
*/