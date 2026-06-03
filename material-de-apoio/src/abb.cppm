export module abb;

import arvores;

import std;

export {

template<typename TipoNo>
TipoNo* minimo(TipoNo* const no) 
pre(no)
post(out : !out->esq) 
{
  auto* atual = no;
  while(atual->esq) atual = atual->esq;
  return atual;
};

template<typename TipoNo>
TipoNo* maximo(TipoNo* const no) 
pre(no)
post(out : !out->dir) 
{
  auto* atual = no;
  while(atual->dir) atual = atual->dir;
  return atual;
};

template<typename TipoNo>
TipoNo* sucessor(TipoNo* const no)   
pre(no)
post(out : implica(no->dir, !out->esq)) 
{
    if(no->dir) return minimo(no->dir);
    auto* atual = no;
    auto* suc = atual->pai;
    while(suc && eh_filho_direito(atual)) {
        atual = suc;
        suc = atual->pai;
    }
    return suc;
}

template<typename TipoNo>
TipoNo* antecessor(TipoNo* no) {
    if(no->esq) return maximo(no->esq);
    auto* p = no->pai;
    while(p && eh_filho_esquerdo(no)) {
        no = p;
        p = no->pai;
    }
    return p;
}


// template<typename TipoNo>
auto* buscaABB(auto* no, char c) {
    if(!no) return no;             // chave não encontrada
    if(no->chave == c) return no;  // chave encontrada
    if(c < no->chave)
        return buscaABB(no->esq, c);  // recursão esquerda
    else
        return buscaABB(no->dir, c);  // recursão direita
}

/*
template<typename TipoNo>
TipoNo* extrai(TipoNo* const no) 
pre(tem_um_ou_zero_filhos(no))
post(tem_zero_filhos(no))
{
    auto* filho = no->esq ? no->esq : no->dir;
    auto* pai   = no->pai;

    if (filho) filho->pai = no->pai;
    no->esq = no->dir = 0;

    if (pai) {
        if (no == pai->esq) pai->esq = filho;
        else                pai->dir = filho;
    }

    return pai;
}
*/

void insereABB(char c, NoEnc5* no) 
pre(no)
{
  if(c <= no->chave) {
      if(no->esq) insereABB(c, no->esq);
      else no->esq = new NoEnc5{.chave=c, .esq=0, .dir=0, .pai=no};
  } 
  else {
      if(no->dir) insereABB(c, no->dir);
      else no->dir = new NoEnc5{.chave=c, .esq=0, .dir=0, .pai=no}; 
  }
}


void upsertABB(char c, float v, NoEnc6* no)
pre(no)
{
   if (c == no->chave) { no->dado = v; return; }
   if (c < no->chave) {
      if (no->esq) upsertABB(c, v, no->esq);
      else no->esq = new NoEnc6{.chave=c,.dado=v,.esq=0,.dir=0,.pai=no};
   } else {
      if (no->dir) upsertABB(c, v, no->dir);
      else no->dir = new NoEnc6{.chave=c,.dado=v,.esq=0,.dir=0,.pai=no};
   }
}

// retorna par( Removeu?, Nova Raiz)
auto removeABB(char c, auto* raiz) {
  if(!raiz) return std::tuple{false, raiz};
  auto* no = ::buscaABB(raiz, c);
  if(!no)   return std::tuple{false, raiz};
  if(tem_dois_filhos(no)) {
    auto* removido = sucessor(no);
    // 'removido' não tem filho esquerdo
    extrai(removido);
    no->chave = removido->chave;
    delete removido;
    return std::tuple{true, raiz};
  } else {
    // 'no' tem no máximo um filho
    auto [pai, filho]  = extrai(no); 
    delete no;    
    if (!pai) return std::tuple{true, filho};
    return std::tuple{true, raiz};
  }
}

} // export

export struct ABB {
  NoEnc5* raiz;    // raiz da árvore
  int N;

  void cria() {
    N = 0;
    raiz = 0;
  }

  void preordem() {
    std::print("Pre-ordem ABB:\t");
    ::preordem(raiz);
    std::println();
  }

  void emordem() {
    std::print("Em ordem ABB:\t");
    ::emordem(raiz);
    std::println();
  }

  NoEnc5* busca(char c) {
      return ::buscaABB(raiz, c);
  }

  void insere(char c) {
    if(!raiz) raiz = new NoEnc5{.chave = c, .esq=0, .dir=0, .pai=0};
    else ::insereABB(c, raiz);
    N++;
  }

  bool remove(char c) {
    auto [b, nraiz] = ::removeABB(c, raiz);
    raiz = nraiz;
    if(b) N--;
    return b;
  }

  /*
  bool remove(char c) {
    if(!raiz) return false;
    auto* no = busca(c);
    if(!no) return false;

    if(no->esq && no->dir) {
      auto* removido = sucessor(no);
      // 'removido' não tem filho esquerdo
      extrai(removido);
      no->chave = removido->chave;
      delete removido;
    } else {
      // 'no' tem no máximo um filho
      auto [pai, filho]  = extrai(no);     
      if (!pai) raiz = filho;
      delete no;
    }

    return true;
  }
  */

  void libera() {
    if(raiz) ::destroi_bin(raiz);
    raiz = 0;
  }

  /*
  void destroi_rec(auto* no) {
    if(no) {
      destroi_rec(no->esq);
      destroi_rec(no->dir);
      delete no;
    }
  }
    */
};

