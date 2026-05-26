
#include<iostream>

class No
{
public:
    int valor;
    No* esq;
    No* dir;
};

class Arvore
{
public:
    No* raiz;
};

//           50
//         /    \\
//        30      70
//                / \\
//              60 
//
// h(50) = 3  (50 -> 70 -> 60)
// h(30) = 1  (30)
// h(70) = 2  (70 -> 60)
// h(60) = 1  (60)

int altura(No* no)
{
    if(!no)
        return 0;
    int h_esq = altura(no->esq);
    int h_dir = altura(no->dir);
    // altura do pai é maior altura dos filhos mais 1
    if(h_esq > h_dir)
        return h_esq + 1;
    else
        return h_dir + 1;
}

int main()
{
    auto no_30 = new No{.valor=30, .esq=0, .dir=0};
    auto no_60 = new No{.valor=60, .esq=0, .dir=0};
    auto no_70 = new No{.valor=70, .esq=no_60, .dir=0};
    auto no_50 = new No{.valor=50, .esq=no_30, .dir=no_70};

    printf("h(30)=%d\n", altura(no_30));
    printf("h(60)=%d\n", altura(no_60));
    printf("h(70)=%d\n", altura(no_70));
    printf("h(50)=%d\n", altura(no_50));

    return 0;
}