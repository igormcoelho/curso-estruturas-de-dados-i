#include<assert.h>
//#include "abb.hpp"

import abb;

import std;

int main() { 
    ABB abb;
    abb.cria();
    abb.insere('M');
    abb.insere('D');
    abb.insere('B');
    abb.insere('F');
    abb.insere('E');
    abb.insere('L');
    abb.insere('O');
    abb.insere('N');
    abb.insere('S');

    abb.preordem();
    abb.emordem();

    imprime_vertical(abb.raiz);
    
    auto* cmin=minimo(abb.raiz);
    auto* cmax=maximo(abb.raiz);

    std::println("cmin={} cmax={}", cmin->chave, cmax->chave);

    auto* no = abb.busca('F');
    std::println("no={} no->pai={}", no->chave, no->pai->chave);

    auto* suc = sucessor(no);
    std::println("sucessor de no={} suc={}", no->chave, suc->chave);
    
    auto* suc2 = sucessor(suc);
    std::println("sucessor de suc={} suc2={}", suc->chave, suc2->chave);

    auto* no2 = abb.busca('O');
    std::println("no2={} no2->pai={}", no2->chave, no2->pai->chave);

    auto* ant = antecessor(no2);
    std::println("antecessor de no2={} ant={}", no2->chave, ant->chave);
    
    auto* ant2 = antecessor(ant);
    std::println("antecessor de ant={} ant2={}", ant->chave, ant2->chave);

    imprime_vertical(abb.raiz);

    std::println("-L");
    abb.remove('L');
    imprime_vertical(abb.raiz);

    std::println("-F");
    abb.remove('F');
    imprime_vertical(abb.raiz);

    std::println("-D");
    abb.remove('D');
    imprime_vertical(abb.raiz);

    std::println("-M");
    abb.remove('M');
    imprime_vertical(abb.raiz);

    std::println("-Z");
    abb.remove('Z');
    imprime_vertical(abb.raiz);

    abb.destroi();

    return 0; 
}