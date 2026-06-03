export module avl;

import arvores;
//import abb;

import std;

export template<typename TipoNo>
void imprime_vertical_dict(TipoNo* raiz) {
    if (!raiz) { std::println("(vazia)"); return; }

    int h = altura(raiz);
    std::queue<TipoNo*> fila;
    fila.push(raiz);

    for (int lv = 0; lv < h; lv++) {
        int largura_nivel = fila.size();
        // 2^(h-lv-1) - 1
        int antes  = (1 << (h - lv - 1)) - 1;  
        // 2^(h-lv)   - 1
        int entre  = (1 << (h - lv))     - 1;  

        for (int i = 0; i < largura_nivel; i++) {
            auto* no = fila.front(); fila.pop();

            if (i == 0)
                for (int t = 0; t < antes; t++) std::print("    ");
            else
                for (int t = 0; t < entre; t++) std::print("    ");

            if (no) {
                std::print("{}({})", no->chave, no->dado);
                fila.push(no->esq);
                fila.push(no->dir);
            } else {
                std::print("    ");
                fila.push(nullptr);
                fila.push(nullptr);
            }
        }
        std::println("");
    }
}

int get_altura(const NoEnc7* no) {
   return no ? no->h : 0; 
}

int calc_altura(const NoEnc7* no) 
pre(no)
{ 
    int he = get_altura(no->esq);
    int hd = get_altura(no->dir);
    return 1 + (he > hd? he : hd); 
}

int fb(const NoEnc7* no)
pre(no) 
{ return get_altura(no->esq) - get_altura(no->dir); }

NoEnc7* rotDir(NoEnc7* const raiz) 
pre(raiz)
{
    auto* x = raiz->esq;
    raiz->esq = x->dir;
    if(x->dir) x->dir->pai = raiz;
    x->dir = raiz;
    x->pai = raiz->pai;
    raiz->pai = x;
    raiz->h = calc_altura(raiz);
    x->h    = calc_altura(x);
    return x;  // nova raiz
}

NoEnc7* rotEsq(NoEnc7* const raiz) {
    auto* x = raiz->dir;
    raiz->dir = x->esq;
    if(x->esq) x->esq->pai = raiz;
    x->esq = raiz;
    x->pai = raiz->pai;
    raiz->pai = x;
    raiz->h = calc_altura(raiz);
    x->h    = calc_altura(x);
    return x; // nova raiz
}

bool eh_regulado(auto* no) 
pre(no)
{
    return fb(no) == 1 || fb(no) == 0 || fb(no) == -1;
} 

NoEnc7* balanceia(NoEnc7* const raiz) 
pre(raiz)
post(out: eh_regulado(out))
{
    int f = fb(raiz);
    if (f > 1) {
        if (fb(raiz->esq) < 0)
            raiz->esq = rotEsq(raiz->esq);
        return rotDir(raiz);
    }
    if (f < -1) {
        if (fb(raiz->dir) > 0)
            raiz->dir = rotDir(raiz->dir);
        return rotEsq(raiz);
    }
    return raiz; // sem rotação necessária!
}

NoEnc7* upsertAVL(char c, float d, NoEnc7* const raiz) 
pre(raiz)
{  
    if (c == raiz->chave) { raiz->dado = d; return raiz; }

    if (c < raiz->chave) {
        if (raiz->esq) raiz->esq = upsertAVL(c, d, raiz->esq);
        else raiz->esq = new NoEnc7{.chave=c, .dado=d, .h=1, .esq=0, .dir=0, .pai=raiz};
    } else {
        if (raiz->dir) raiz->dir = upsertAVL(c, d, raiz->dir);
        else raiz->dir = new NoEnc7{.chave=c, .dado=d, .h=1, .esq=0, .dir=0, .pai=raiz};
    }

    raiz->h = calc_altura(raiz);
    // sempre muda altura!!! até a raiz da árvore...

    return balanceia(raiz);
}

export struct AVL {
  NoEnc7* raiz;    // raiz da árvore
  int N;

  void cria() {
    N = 0;
    raiz = 0;
  }

  void libera() {
    if(raiz) ::destroi_bin(raiz);
    raiz = 0;
  }

  void upsert(char c, float d) {
    if(!raiz) raiz = new NoEnc7{.chave=c, .dado=d, .h=1, .esq=0, .dir=0, .pai=0};
    else raiz = ::upsertAVL(c, d, raiz);
    N++;
  }


};
