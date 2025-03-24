// C23 or C++23
// import std;
#include <stdint.h>
#include <stdio.h>

// #include <cstddef>
// #include <cstdint>

int main() {
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
    unsigned int x = 10;         // 10
    double y1 = x / -2;          // 0
    double y2 = (double)x / -2;  // -5
    // double y3 = static_cast<double>(x) / -2;  // -5 (C++)
    const unsigned int z1 = x;  // 10
    // z1 = 20;                    // ERRO
    printf("%u %f %f %u\n", x, y1, y2, z1);
  }

  return 0;
}
