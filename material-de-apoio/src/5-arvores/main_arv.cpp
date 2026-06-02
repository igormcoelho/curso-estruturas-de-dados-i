
import arvores;

import std;

int main() {

    auto* no_C = new NoEnc3{.chave = 'C', .esq=0, .dir=0};
    auto* no_D = new NoEnc3{.chave = 'D', .esq=0, .dir=0};
    auto* no_B = new NoEnc3{.chave = 'B', .esq=no_D, .dir=0};
    auto* no_A = new NoEnc3{.chave = 'A', .esq=no_B, .dir=no_C};
    auto* raiz = no_A;

    int h = altura(raiz);
    int niv = nivel(no_C, raiz);

    std::println("h={} nivel={}", h, niv);

    destroi_bin(raiz);

    return 0;
}