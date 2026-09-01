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

struct NoEnc7 {
   char chave;     // chave de busca
   float dado;     // valor armazenado
   int h;          // altura
   NoEnc7* esq;    // filho esquerdo
   NoEnc7* dir;    // filho direito
   NoEnc7* pai;    // pai
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


// endereçamento estilo heap
struct NoSeq1 {
    int id;
};

// absolute 
int absv(int val) {
    return val > 0? val:-val;
}

NoSeq1 pai(NoSeq1 no) 
pre(no.id >= 0)
{
    if(no.id==0) return {-1}; // NULL
    else         return {(no.id - 1) / 2};
}

NoSeq1 filho_esq(NoSeq1 no) 
pre(no.id >= 0)
{
    return {2 * no.id + 1};
}

NoSeq1 filho_dir(NoSeq1 no) 
pre(no.id >= 0)
{
    return {2 * no.id + 2};
}

void inverte(NoSeq1 no, int v[]) 
pre(no.id != -1)
{
    v[no.id] = -v[no.id];
}

// sobe invertendo sinal
void sobe_inverte(int v[], int MAXN, int N, NoSeq1 no) 
pre(no.id != 0)
{
    inverte(no, v);
    if(pai(no).id != -1)
        sobe_inverte(v, MAXN, N, pai(no));
}


bool vazio(NoSeq1 no, int v[]) 
pre(no.id >= 0)
{
    return {v[no.id] == 0};
}

bool existe(NoSeq1 no, int v[]) {
    return no.id >= 0 && !vazio(no, v);
}

bool tem_filho_esq(NoSeq1 no, int v[]) 
pre(no.id >= 0)
{
    NoSeq1 fe = filho_esq(no);
    if(fe.id == -1) return false;
    if(vazio(fe, v)) return false;
    return true;
}

NoSeq1 minimo(NoSeq1 no, int v[]) 
pre(no.id >= 0)
/// post(out : !out->esq) /// SEM ESQUERDA!
{
  NoSeq1 atual = no;
  while(tem_filho_esq(atual, v)) atual = filho_esq(atual);
  return atual;
};

bool eh_filho_esquerdo(NoSeq1 f, int v[]) 
pre(existe(f, v) && existe(pai(f), v))
{
    return f.id == filho_esq(pai(f)).id;
} 

bool eh_filho_direito(NoSeq1 f, int v[]) 
pre(existe(f, v) && existe(pai(f), v))
{
    return f.id == filho_dir(pai(f)).id;
} 


void sobe_inverte_removendo(NoSeq1 no, int v[]) 
pre(no.id != -1)
{
    if(pai(no).id != -1) {
        if(eh_filho_direito(no, v)) {
            if(v[pai(no).id] < 0) { // mais leve à esquerda, OK!
                inverte(no, v);
                std::println("INVERTE no={} val={}", no.id, v[no.id]);
            }
            else
                std::println("PROBLEMAAA!!! ESQ LEVE E TIROU MAIS!!!");
        }
        else  // filho esquerdo
        {
            if(v[pai(no).id] > 0) // mais leve à direita, OK!
                inverte(no, v);
            else
                std::println("PROBLEMAAA!!! DIR LEVE E TIROU MAIS!!!");
        }
    }
    else {
        inverte(no, v);
        std::println("SO INVERTE {}... mas vai saber! Pq não tem pai...", v[no.id]);
    }
    
    if(pai(no).id != -1)
        sobe_inverte_removendo(pai(no), v);
}

// extrai elemento que só tem um filho direito ou esquerdo
int extrai_troca_filho(NoSeq1 no, int v[]) 
/// pre(tem_um_ou_zero_filhos(no))
/// post(tem_zero_filhos(no))
{
    NoSeq1 filho = existe(filho_esq(no), v) ? filho_esq(no) : filho_dir(no);
    int val_filho = v[filho.id];
    v[filho.id] = 0; // apaga filho
    int val_no = v[no.id];
    v[no.id] = val_filho; // substitui nó
    return val_no;
}


export
bool insereBinRec(int v[], int MAXN, int N, NoSeq1 no, int _chave) 
pre(!vazio(no, v))
{
    int chave = absv(_chave);
    std::println("add chave={} no={}", chave, no.id);
    if(v[no.id]>0 && chave <  absv(v[no.id])) {
        // sinal esquerda e vai pra esquerda
        if(!vazio(filho_esq(no), v)) {
            return insereBinRec(v, MAXN, N, filho_esq(no), chave);
        }
        else {
           // insere (positivo)!
           v[filho_esq(no).id] = chave;
           inverte(no, v); // inverte sinal!
           if(pai(no).id != -1 )
             sobe_inverte(v, MAXN, N, pai(no));
           return true; // FIM
        }
    }
    if(v[no.id]<0 && chave > absv(v[no.id])) {
        // sinal direita e vai pra direita
        if(!vazio(filho_dir(no), v)) {
            return insereBinRec(v, MAXN, N, filho_dir(no), chave);
        }
        else {
           // insere (positivo)!
           v[filho_dir(no).id] = chave;
           inverte(no, v); // inverte sinal!
           if(pai(no).id != -1 )
             sobe_inverte(v, MAXN, N, pai(no));
           return true; // FIM
        }
    }

    if(v[no.id]>0 && chave > absv(v[no.id])) {
        // sinal esquerda e vai pra direita
        // esquerda leve, direita mais pesada... mover alguem da direita pra esquerda!
        // passo 1: pega o sucessor de nó e extrai ele (nunca terá filho esquerdo e só terá um direito!)
        std::println("AQUI!");
        NoSeq1 fd = filho_dir(no);
        if(vazio(fd, v)) fd.id = -1; // nao existe
        if(existe(fd, v)) {
             fd = minimo(fd, v);
             int val_backup = v[fd.id];
             int val2 = extrai_troca_filho(fd, v);
             std::println("val_backup={} val2={}", val_backup, val2);
             // agora SOBE atualizando...
             if(existe(fd, v))
                sobe_inverte_removendo(fd, v);
            else
                sobe_inverte_removendo(no, v); // nao sobrou ninguem lá!
            int val_reinsere = v[no.id];
            int sinal = val_reinsere < 0 ? -1 : +1;
            v[no.id] = absv(val_backup)*sinal;
            std::println("reinserindo val = {}", val_reinsere);
            insereBinRec(v, MAXN, N, filho_esq(no), val_reinsere);
        } else {
            std::println("NAO TEM MINIMO!!!!!");
        }

        std::println("MINIMO = {} ({})", fd.id, v[fd.id]);
    }

    std::println("E AGORA!?");
    return false;
}



export
void insereBin(int v[], int MAXN, int N, int _val) {
    int val = absv(_val);
    if(N == 0) {
        v[0] = val;
        return;
    }
    NoSeq1 raiz {0};
    insereBinRec(v, MAXN, N, raiz, val);
}



export
void printv(int v[], int N) {
    std::print("V: ");
    for(int i=0; i<N;i++)
        std::print("{} ", v[i]);
    std::println();
}