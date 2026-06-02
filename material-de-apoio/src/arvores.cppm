export module arvores;

import std;

// #include<assert.h>

template <typename Ptr, typename T>
concept deref = requires(Ptr p) {
    { *p } -> std::same_as<T&>;
};

// Só usar conceitos em ULTIMO CASO!
template <typename T>
concept NoBin = requires(T t) {
    { t.chave };
    { t.esq } -> deref<T>;
    { t.dir } -> deref<T>;
};

template <typename T>
concept NoBinPai = NoBin<T> && requires(T t) {
    { t.pai } -> std::same_as<T>;
};

export {
// a => b (a implica b)
// ou algum dia... https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2025/p2971r3.pdf
constexpr bool implica(bool a, bool b) { return !a || b; }

// Exemplo de nó binário: NoEnc3
struct NoEnc3 {
   char chave;     // dado armazenado
   NoEnc3* esq;    // filho esquerdo
   NoEnc3* dir;    // filho direito
};

struct NoEnc4 {
   char chave;                     // dado armazenado
   std::unique_ptr<NoEnc4> esq;    // filho esquerdo
   std::unique_ptr<NoEnc4> dir;    // filho direito
};

// Exemplo de nó binário com pai: NoEnc5
struct NoEnc5 {
   char chave;     // dado armazenado
   NoEnc5* esq;    // filho esquerdo
   NoEnc5* dir;    // filho direito
   NoEnc5* pai;    // pai
};

// Exemplo de nó binário com chave e valor: NoEnc6
struct NoEnc6 {
   char chave;     // chave de busca
   float dado;     // valor armazenado
   NoEnc6* esq;    // filho esquerdo
   NoEnc6* dir;    // filho direito
   NoEnc6* pai;    // pai
};

// template<NoBin TipoNo>
auto altura(auto* const no) -> int {
    if (!no) return 0;
    int he = altura(no->esq);
    int hd = altura(no->dir);
    return 1 + (he > hd ? he : hd);
}

// template<NoBin TipoNo>
int nivel(auto* no, auto* raiz) {
    if (!raiz) return 0;
    if (no == raiz) return 1;
    int esq = nivel(no, raiz->esq);
    if (esq != 0) return 1+esq;
    int dir = nivel(no, raiz->dir);
    if (dir != 0) return 1 + dir;
    return 0; // nós em árvores distintas
}

// template<NoBin TipoNo>
int nivel2(auto* no, auto* raiz, int n = 0) {
    if (!raiz) return -1;
    if (no == raiz) return n;
    int esq = nivel2(no, raiz->esq, n + 1);
    if (esq != -1) return esq;
    return nivel2(no, raiz->dir, n + 1);
}

void destroi_bin(auto* no) {
    if(no) {
        destroi_bin(no->esq);
        destroi_bin(no->dir);
        delete no;
    }
}

// Exemplos de preordem, etc
// Não são genéricos (com lambda) intencionalmente!

void preordem(auto* no) {
  if(!no) return;
  std::print("{} ", no->chave);
  preordem(no->esq);
  preordem(no->dir);
} 

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


bool eh_filho_direito(auto* f) 
pre(f && f->pai)
{
    return f == f->pai->dir;
} 

bool eh_filho_esquerdo(auto* f) 
pre(f && f->pai)
{
    return f == f->pai->esq;
} 

} // export 

export template<typename TipoNo>
void imprime_vertical(TipoNo* raiz) {
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

export
// template<typename TipoNo>
auto extrai(auto* const no) 
pre(tem_um_ou_zero_filhos(no))
post(tem_zero_filhos(no))
{
    auto* filho = no->esq ? no->esq : no->dir;
    auto* pai   = no->pai;
    if (filho) filho->pai = pai;
    if (pai) {
        if (eh_filho_esquerdo(no)) pai->esq = filho;
        else                       pai->dir = filho;
    }
    no->pai = no->esq = no->dir = 0;
    return std::tuple{pai, filho};
}


