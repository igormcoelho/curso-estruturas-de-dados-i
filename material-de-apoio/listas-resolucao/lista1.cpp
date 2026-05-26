
#include<iostream>
#include<queue>

// Quais operações de uma pilha?
// topo           ->  O(1)  "tempo constante"
// empilhar       ->  O(1)  "tempo constante"
// desempilhar    ->  O(1)  "tempo constante"

// Quais operações de uma fila?
// frente         ->  O(1)  "tempo constante"
// enfileira      ->  O(1)  "tempo constante"
// desenfileira   ->  O(1)  "tempo constante"

// Resumo da Pilha2F (complexidade)
// topo           O(1) "constante"
// empilhar       O(N) "linear"
// desempilhar    O(1) "constante"



// Pilha construída por duas Filas
class Pilha2F
{
public:
    // VETOR xxxx
    std::queue<int> fila1, fila2;
    // N : tamanho do problema = |fila1| + |fila2| = |fila1| (pq fila2 é vazia)

    int tamanho()
    {
        return fila1.size();
    }

    void cria()
    {
        fila1 = std::queue<int>{};
        fila2 = std::queue<int>{};
    }
    //  fila1: 10 (FRENTE)
    //  fila1: 20 -> 10  (FRENTE) - ERRADO!

    //  fila2: 10
    //  fila1: 10 -> 20
    int topo()          // Complexidade: Theta(1)
    {
        return fila1.front(); // Complexidade = O(1) + O(1) = O(1)
    }
    void empilha(int x) // Complexidade: Theta(N)
    {
        // primeiro passo: mover todos da fila1 para fila2
        while(fila1.size() > 0) // N * O(1) = O(N)
        {
            fila2.push(fila1.front()); // O(1) + O(1) = O(1)
            fila1.pop();               // O(1)
            // bloco: O(1) "~~~ constante 3"
        }
        // segundo passo:  adiciona elemento na fila1
        fila1.push(x);     // O(1)
        // terceiro passo: mover elementos da fila2 para fila1
        while(fila2.size() > 0) // N * O(1) = O(N)
        {
            fila1.push(fila2.front()); // O(1) + O(1) = O(1)
            fila2.pop();               // O(1)
            // bloco: O(1) "~~~ constante 3"
        }
        // bloco: O(N) + O(1) + O(N) = O(N)
        // ~~~ N*3 + 1 + N*3 = 6*N + 1 === O(N)          SIM
        //                             === O(N^2)        SIM
        //                             === O(log N)      NÃO! (ERRADO)
        //                             === Omega(N)      SIM
        //                             === Omega(N^2)    NÃO! (ERRADO)
        //                             === Omega(log N)  SIM 
        //                             === Omega(1)      SIM
        //                             === Theta(N) = Omega(N) ^ O(N)  SIM
        // bloco: Theta(N)
    }
    int desempilha() // Complexidade: Theta(1)
    {
        int f = fila1.front(); // O(1)
        fila1.pop();           // O(1)
        return f;              // O(1)
        // bloco: O(1)+O(1)+O(1) = O(1)
    }
};

//int metodo(int x1, int x2)
//{
//    printf("x1=%d\n", x1);
//    printf("x2=%d\n", x2);
//}

int main()
{
    Pilha2F pf;
    pf.cria();
    pf.empilha(10);
    pf.empilha(20);
    pf.empilha(30);
    printf("%d\n", pf.desempilha()); // 30
    printf("%d\n", pf.desempilha()); // 20
    pf.empilha(40);
    //printf("%d\n", pf.desempilha()); // 40
    //printf("%d\n", pf.desempilha()); // 10
    int f1 = pf.desempilha(); // 40
    int f2 = pf.desempilha(); // 10
    printf("%d %d\n", f1, f2); // ?? ??
    //metodo(pf.desempilha(), pf.desempilha());

    int N=10000;
    while(N--)
        pf.empilha(N);
    while(pf.tamanho() > 0)
        pf.desempilha();
    
    
    return 0;
}

