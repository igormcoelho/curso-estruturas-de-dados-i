// C23 or C++23
// import std;
#include <stdint.h>
#include <stdio.h>

#include <expected>
#include <memory>
#include <optional>
#include <print>
#include <span>
#include <vector>
// #include <cstddef>
// #include <cstdint>
using std::print;
using std::println;

auto imprime(int a, int b) -> void {
  for (auto i = a; i < b; i++) println("{}\n", i);
}

class MyVoid {
 public:
  auto f() -> void {}
};

auto duplo(int p) { return std::tuple{p + 3, p + 6.5}; }

auto busca(char c, std::span<char> v) -> std::optional<int> {
  // busca char 'c' num vetor v e retorna posição
  for (int i = 0; i < v.size(); i++)
    if (v[i] == c) return i;  // encontrou
  // não encontrou
  return std::nullopt;
}

auto busca2(char c, std::span<char> v) -> std::expected<int, std::string> {
  // busca char 'c' num vetor v e retorna posição
  for (int i = 0; i < v.size(); i++)
    if (v[i] == c) return i;  // encontrou
  // não encontrou
  return std::unexpected{"não encontrou"};
}

template <typename Agregado>
concept TemNegativo = requires(Agregado a) {
  { a.neg() } -> std::same_as<void>;
};

class Z {
 public:
  int x;
  auto neg() -> void { println("{}", -1 * (this->x)); }
};

int main(int argc, char* argv[]) {
  {
    int x = 5;      // armazena o inteiro 5 na variável x
    char y = 'A';   // armazena o caractere 'A' na variável y
    float z = 3.7;  // armazena o real 3.7 na variável z
    bool a = true;  // armazena o booleano true na variável a
    auto b = 'B';   // prefira dedução de tipo com 'auto'
  }

  {
    int x1 = 5;           // => 5
    int x2 = x1 + 10;     // => 15
    int x3 = x2 / 2;      // => 7
    float x4 = x2 / 2;    // => 7.0
    float x5 = x2 / 2.0;  // => 7.5
    auto x6 = 15;         // => 15   (C warning: Wimplicit-int)
    auto x7 = x2 / 2;     // => ?    (C warning: Wimplicit-int)
    auto x8 = x2 / 2.0;   // => ?    (C warning: Wimplicit-int)

    printf("x1=%d x2=%d x3=%d x4=%f x5=%f x6=%d x7=%d x8=%f\n", x1, x2, x3, x4,
           x5, x6, x7, x8);

    // C++: x1=5 x2=15 x3=7 x4=7.000000 x5=7.500000 x6=15 x7=7 x8=7.500000
    // C:   x1=5 x2=15 x3=7 x4=7.000000 x5=7.500000 x6=15 x7=7 x8=7.500000
  }

  {
    int64_t x1 = 10;  // long (ou long long)
    int32_t x2 = 20;  // int
    int16_t x3 = 30;  // short
    int8_t x4 = 40;   // signed char
    uint8_t x5 = 50;  // unsigned char
    // std::byte b{60};  // unsigned char // somente C++
  }

  {
    // Em C (tipo agregado P)
    struct P {
      int32_t x;
      char y;
    };

    // declara variável tipo P
    struct P p1;
    // designated initializers
    struct P p2 = {.x = 10, .y = 'Y'};
  }

  {
    constexpr int x = 10;
    printf("%d\n", x);
  }

  {
    unsigned int x = 10;                      // 10
    double y1 = x / -2;                       // 0
    double y2 = (double)x / -2;               // -5
    double y3 = static_cast<double>(x) / -2;  // -5 (C++)
    const unsigned int z1 = x;                // 10
    // z1 = 20;                   // ERRO
    std::println("{} {} {} {} {}", x, y1, y2, y3, z1);
  }
  {
    std::string s1 = "abcd";
    std::string s2 = "ef";
    println("tamanho1={} tamanho2={}", s1.length(), s2.length());
    // tamanho1=4 tamanho2=2
    s1 = s1 + s2;
    std::string_view sv = s1;
    std::string_view sub = sv.substr(3, 2);
    println("s1={} s2={} sv={} sub={}", s1, s2, sv, sub);
    // s1=abcdef s2=ef sv=abcdef sub=de
    const char* cs = s1.c_str();
    println("s1={} cs={}", s1, cs);
    // s1=abcdef cs=abcdef
  }

  {
    int v1[10];
    int v2[] = {1, 2, 3, 4};
    println("v[0]={} v[3]={} tam={}", v2[0], v2[3], sizeof(v2) / sizeof(v2[0]));
    // v[0]=1 v[3]=4 tam=4
    std::vector<int> k1{};
    std::vector<int> k2 = {1, 2, 3, 4};
    k2.push_back(999);
    println("k[0]={} k[4]={} tam={}", k2[0], k2[4], k2.size());
    // k[0]=1 k[4]=999 tam=5
    println("{}", std::is_aggregate<std::vector<int>>::value);
    // false
  }
  {
    int v1[10];
    int v2[] = {1, 2, 3, 4};
    std::array<int, 10> a1{};
    std::array<int, 4> a2 = {1, 2, 3, 4};
    print("v[0]={} v[3]={} tam={}\n", v2[0], v2[3], sizeof(v2) / sizeof(v2[0]));
    // v[0]=1 v[3]=4 tam=4
    print("a[0]={} a[3]={} tam={}\n", a2[0], a2[3], a2.size());
    // a[0]=1 a[3]=4 tam=4
    print("{} {} {}\n", std::is_aggregate<int*>::value,
          std::is_aggregate<int[]>::value,
          std::is_aggregate<std::array<int, 4>>::value);
    // false true true
  }
  {
    std::println("std::span!");
    // ./programa 1 2 3
    int v2[] = {1, 2, 3, 4};
    std::span<int> s1{v2};
    for (auto i : s1) std::println("{}", i);
    // 1 2 3 4
    std::vector<int> vec = {1, 2, 3, 4};
    std::span<int> s2{vec};
    for (auto i : s2) std::println("{}", i);
    // 1 2 3 4
    std::span<char*> entrada{argv, argc};
    for (auto i : entrada) std::println("{}", i);
    // ./programa 1 2 3
  }
  {
    std::println("imprime!");
    imprime(1, 4);
  }
  {
    MyVoid vf;
    vf.f();
  }
  {
    auto [x1, x2] = duplo(10);  // x1=13 x2=16.5
    std::println("{} {}", x1, x2);
  }
  {
    std::vector<char> v = {'a', 'b', 'c'};
    auto op = busca('x', v);
    if (op)
      println("posicao={}", *op);
    else
      println("não encontrou");
  }
  {
    std::vector<char> v = {'a', 'b', 'c'};
    auto exp = busca2('x', v);
    if (exp)
      println("posicao={}", *exp);
    else
      println("{}", exp.error());
  }
  {
    static_assert(TemNegativo<Z>);
  }
  {
    auto p1 = std::make_unique<Z>(Z{.x = 10});
  }

  return 0;
}
