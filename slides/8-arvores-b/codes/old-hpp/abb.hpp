#pragma once

import std;

// a => b (a implica b)
// ou algum dia... https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2025/p2971r3.pdf
constexpr bool implica(bool a, bool b) { return !a || b; }

struct NoEnc3 {
   char chave;     // dado armazenado
   NoEnc3* esq;    // filho esquerdo
   NoEnc3* dir;    // filho direito
};

// NoEnc3 com pai
struct NoEnc4 {
   char chave;     // dado armazenado
   NoEnc4* esq;    // filho esquerdo
   NoEnc4* dir;    // filho direito
   NoEnc4* pai;    // pai
};

int altura(auto* no) {
    if (!no) return 0;
    int he = altura(no->esq);
    int hd = altura(no->dir);
    return 1 + (he > hd ? he : hd);
}

int nivel(auto* no, auto* raiz, int n = 0) {
    if (!raiz) return -1;
    if (no == raiz) return n;
    int esq = nivel(no, raiz->esq, n + 1);
    if (esq != -1) return esq;
    return nivel(no, raiz->dir, n + 1);
}


void preordem(auto* no) {
  if(!no) return;
  std::print("{} ", no->chave);
  preordem(no->esq);
  preordem(no->dir);
} 

// TODO: fazer como "METODO SOLTO" em cima de NoEnc3...
// OU SEJA, funciona pra QUALQUER ARVORE!
void emordem(auto* no) {
  if(!no) return;
  emordem(no->esq);
  std::print("{} ", no->chave);
  emordem(no->dir);
}


bool tem_um_ou_zero_filhos(auto* const no) 
pre(no)
{ return !no->esq || !no->dir;}

bool tem_dois_filhos(auto* const no) 
pre(no)
{ return no->esq && no->dir; } 

bool tem_um_filho(auto* const no) 
pre(no)
{ return ((!no->esq) + (!no->dir)) == 1; }

bool tem_zero_filhos(auto* const no) 
pre(no)
{ return !no->esq && !no->dir; } 


bool eh_filho_direito(NoEnc4* f, NoEnc4* p) {
    return f == p->dir;
} 

bool eh_filho_esquerdo(NoEnc4* f, NoEnc4* p) {
    return f == p->esq;
} 

void substitui_filho_no_pai(NoEnc4* f, NoEnc4* p, NoEnc4* novo) {
    if(f == p->esq) p->esq = novo;
    else p->dir = novo;
    f->pai = 0;
}

void remove_filho_do_pai(NoEnc4* f, NoEnc4* p) {
    if(f == p->esq) p->esq = 0;
    else p->dir = 0;
    f->pai = 0;
} 
// OU...
void remove_filho_do_pai2(NoEnc4* f, NoEnc4* p) {
  return substitui_filho_no_pai(f, p, 0);
}


// C++26: pre(no)
template<typename TipoNo>
TipoNo* minimo(TipoNo* const no) 
pre(no)
post(out : !out->esq) 
{
  auto* atual = no;
  while(atual->esq) atual = atual->esq;
  return atual;
};

// C++26: pre(no)
template<typename TipoNo>
TipoNo* maximo(TipoNo* const no) 
pre(no)
post(out : !out->dir) 
{
  auto* atual = no;
  while(atual->dir) atual = atual->dir;
  return atual;
};


NoEnc4* sucessor(NoEnc4* const no)   
pre(no)
post(out : implica(no->dir, !out->esq)) 
{
    if(no->dir) return minimo(no->dir);
    NoEnc4* atual = no;
    NoEnc4* p = atual->pai;
    while(p && eh_filho_direito(atual, p)) {
        atual = p;
        p = atual->pai;
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


template<typename TipoNo>
TipoNo* busca(TipoNo* no, char c) {
    if(!no) return 0;              // chave não encontrada
    if(no->chave == c) return no;  // chave encontrada
    if(c < no->chave)
        return busca(no->esq, c);  // recursão esquerda
    else
        return busca(no->dir, c);  // recursão direita
}

template<typename TipoNo>
void imprime_vertical(TipoNo* raiz) {
    if (!raiz) { std::println(""); return; }

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
            TipoNo* no = fila.front(); fila.pop();

            if (i == 0)
                for (int t = 0; t < antes; t++) std::print(" ");
            else
                for (int t = 0; t < entre; t++) std::print(" ");

            if (no) {
                std::print("{}", no->chave);
                fila.push(no->esq);
                fila.push(no->dir);
            } else {
                std::print(" ");
                fila.push(nullptr);
                fila.push(nullptr);
            }
        }
        std::println("");
    }
}


template<typename TipoNo>
TipoNo* extrai(TipoNo* const no) 
pre(tem_um_ou_zero_filhos(no))
post(tem_zero_filhos(no))
{
    NoEnc4* filho = no->esq ? no->esq : no->dir;
    NoEnc4* pai   = no->pai;

    if (filho) filho->pai = no->pai;
    no->esq = no->dir = 0;

    if (pai) {
        if (no == pai->esq) pai->esq = filho;
        else                pai->dir = filho;
    }

    return pai;
}


struct ABB {
  NoEnc4* raiz;    // raiz da árvore
  int N;

  void cria() {
    N = 0;
    raiz = 0;
  }

  void preordem() {
    std::print("Pre-ordem:\t");
    ::preordem(raiz);
    std::println();
  }

  void emordem() {
    std::print("Em ordem:\t");
    ::emordem(raiz);
    std::println();
  }

  NoEnc4* busca(char c) {
      return ::busca(raiz, c);
  }

  void insere(char c) {
    if(!raiz) raiz = new NoEnc4{.chave = c, .esq=0, .dir=0, .pai=0};
    else insereRec(c, raiz);
  }

  void insereRec(char c, NoEnc4* no) {
    if(c <= no->chave) {
        if(no->esq) insereRec(c, no->esq);
        else no->esq = new NoEnc4{.chave=c, .esq=0, .dir=0, .pai=no};
    } 
    else {
        if(no->dir) insereRec(c, no->dir);
        else no->dir = new NoEnc4{.chave=c, .esq=0, .dir=0, .pai=no}; 
    }
  }

  bool remove(char c) {
    if(!raiz) return false;
    NoEnc4* no = busca(c);
    if(!no) return false;

    if(no->esq && no->dir) {
      auto* removido = sucessor(no);
      // 'removido' não tem filho esquerdo
      extrai(removido);
      no->chave = removido->chave;
      delete removido;
    } else {
      // 'no' tem no máximo um filho
      NoEnc4* pai  = extrai(no);     
      if (!pai) raiz = no->esq ? no->esq : no->dir;
      delete no;
    }

    return true;
  }

  void destroi() {
    if(raiz) destroi_rec(raiz);
    raiz = 0;
  }

  void destroi_rec(NoEnc4* no) {
    if(no) {
      destroi_rec(no->esq);
      destroi_rec(no->dir);
      delete no;
    }
  }



    // retorna pai do elemento removido (?)
    // Como rebalancear posteriormente?
    // Talvez colocar pre(raiz) aqui?? Nao invocar com arvore vazia... nao faz sentido limitar!
    //

    /*
    bool remove(char c) {
      if(!raiz) return false; // excecao? arvore vazia?
      bool removeu = false;
      raiz = removeRec(c, raiz); // substitui pelo sucessor
      return 
    }

    // Retorna nova raiz da subárvore atualizada após remoção
    NoEnc4* removeRec(char c, NoEnc4* no) {
      //
      NoEnc4* p = no->pai;
      if(!no->esq && !no->dir) remove_filho_do_pai(no, p);
      else if(no->dir)
      if(no->esq) return maximo(no->esq);
      NoEnc4* p = no->pai;
      while(p && eh_filho_esquerdo(no, p)) {
          no = p;
          p = no->pai;
      }
      return p;
    }


    // pre(no->pai != 0) // C++26
    void remove(NoEnc4* no) {
        assert(no->pai != 0);
        //
        NoEnc4* p = no->pai;
        if(!no->esq && !no->dir) remove_filho_do_pai(no, p);
        else if(no->dir)
        if(no->esq) return ::maximo(no->esq);
        NoEnc4* p = no->pai;
        while(p && eh_filho_esquerdo(no, p)) {
            no = p;
            p = no->pai;
        }
        return p;
    }
    */
};

