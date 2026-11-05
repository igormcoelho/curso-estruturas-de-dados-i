import std;

// TODO: NoEnc5* com altura...
struct NoEnc4 {
   char chave;     // dado armazenado
   NoEnc4* esq;    // filho esquerdo
   NoEnc4* dir;    // filho direito
   NoEnc4* pai;    // pai
   int h;
};

bool eh_filho_direito(NoEnc4* x, NoEnc4* y) {
    // se x é filho direito de y
    return x == y->dir;
} 

bool eh_filho_esquerdo(NoEnc4* x, NoEnc4* y) {
    // se x é filho esquerdo de y
    return x == y->esq;
} 

struct AVL {
  NoEnc4* raiz;    // raiz da árvore
  int N;

  void cria() {
    N = 0;
    raiz = 0;
  }

  void insere(char c) {
    if(!raiz) raiz = new NoEnc4{.chave = c, .esq=0, .dir=0, .pai=0, .h=1};
    else insereRec(c, raiz);
  }

  void insereRec(char c, NoEnc4* no) {
    if(c <= no->chave) {
        if(no->esq) insereRec(c, no->esq);
        else no->esq = new NoEnc4{.chave=c, .esq=0, .dir=0, .pai=no, .h=1};
    } 
    else {
        if(no->dir) insereRec(c, no->dir);
        else no->dir = new NoEnc4{.chave=c, .esq=0, .dir=0, .pai=no, .h=1}; 
    }
  }

  void preordem() {
    std::print("Pre-ordem:\t");
    preordem(raiz);
    std::println();
  }

  void preordem(NoEnc4* no) {
    if(!no) return;
    std::print("{} ({}) ", no->chave, no->h);
    preordem(no->esq);
    preordem(no->dir);
  } 

  void emordem() {
    std::print("Em ordem:\t");
    emordem(raiz);
    std::println();
  }

  // TODO: fazer como "METODO SOLTO" em cima de NoEnc3...
  // OU SEJA, funciona pra QUALQUER ARVORE!
  void emordem(NoEnc4* no) {
    if(!no) return;
    emordem(no->esq);
    std::print("{} ({}) ", no->chave, no->h);
    emordem(no->dir);
  }

  // C++26: pre(no)
  NoEnc4* minimo(NoEnc4* no) {
    while(no->esq) no = no->esq;
    return no;
  };

  // C++26: pre(no)
  NoEnc4* maximo(NoEnc4* no) {
    while(no->dir) no = no->dir;
    return no;
  };

    NoEnc4* buscaABB(NoEnc4* no, char c) {
        if(!no) return 0;                 // chave não encontrada
        if(no->chave == c) return no;     // chave encontrada
        if(c < no->chave)
            return buscaABB(no->esq, c);  // recursão esquerda
        else
            return buscaABB(no->dir, c);  // recursão direita
    }

    NoEnc4* sucessor(NoEnc4* no) {
        if(no->dir) return minimo(no->dir);
        NoEnc4* p = no->pai;
        while(p && eh_filho_direito(no, p)) {
            no = p;
            p = no->pai;
        }
        return p;
    }

    NoEnc4* antecessor(NoEnc4* no) {
        if(no->esq) return maximo(no->esq);
        NoEnc4* p = no->pai;
        while(p && eh_filho_esquerdo(no, p)) {
            no = p;
            p = no->pai;
        }
        return p;
    }


};



int main() { 
    AVL abb;
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
    
    auto* cmin=abb.minimo(abb.raiz);
    auto* cmax=abb.maximo(abb.raiz);

    std::println("cmin={} cmax={}", cmin->chave, cmax->chave);

    auto* no = abb.buscaABB(abb.raiz, 'F');
    std::println("no={} no->pai={}", no->chave, no->pai->chave);

    auto* suc = abb.sucessor(no);
    std::println("sucessor de no={} suc={}", no->chave, suc->chave);
    
    auto* suc2 = abb.sucessor(suc);
    std::println("sucessor de suc={} suc2={}", suc->chave, suc2->chave);

    auto* no2 = abb.buscaABB(abb.raiz, 'O');
    std::println("no2={} no2->pai={}", no2->chave, no2->pai->chave);

    auto* ant = abb.antecessor(no2);
    std::println("antecessor de no2={} ant={}", no2->chave, ant->chave);
    
    auto* ant2 = abb.antecessor(ant);
    std::println("antecessor de ant={} ant2={}", ant->chave, ant2->chave);

    return 0; 
}