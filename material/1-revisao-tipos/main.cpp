#include <fmt/core.h>
using fmt::print;

void teste_loop1() {
  int z = 0;
  int i = 0;
  for (; i < 10; i++) {
    if (i > 5) continue;
    print("z={} i={}\n", z, i);
    z++;
  }
  // z==6
  print("final z={} i={}\n", z, i);
}

void teste_loop2() {
  int z = 0;
  int i = 0;
  while (i < 10) {
    print("z={} i={}\n", z, i);
    z++;
    if (i > 5) break;
    i++;
  }
  // z==7
  print("final z={} i={}\n", z, i);
}

void teste_loop3() {
  int z = 0;
  for (auto i = 0; i < 10; i++) {
    if (i < 5) continue;
    int j = i;
    while (j < 10) {
      if (i > 6) goto fim;
      print("z={} i={} j={}\n", z, i, j);
      z++;
      j++;
    }
  }
fim:
  // z==9: i=5 j=5..9 [5 passos]; i=6 j=6..9 [4 passos]
  print("final z={}\n", z);
}

int main() {
  teste_loop1();
  teste_loop2();
  teste_loop3();
  return 0;
}
