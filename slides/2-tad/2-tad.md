---
author: Igor Machado Coelho
title: Estruturas de Dados I
subtitle: Tipos Abstratos de Dados, Vistas e Ordenação
date: 15/11/2026
transition: linear
fontsize: 10
aspectratio: 169
header-includes:
- <link rel="stylesheet" type="text/css" href="general.css">
- <link rel="stylesheet" type="text/css" href="reveal-beamer.css">
---


# Tipos Abstratos de Dados, Vistas e Ordenação

------

## Pré-Requisitos

São requisitos para essa aula o conhecimento de:

- Introdução/Fundamentos de Programação (em alguma linguagem de programação)
- Interesse em aprender C/C++
- Tipos agregados (`struct`) com métodos, e ponteiros (aula de Introdução)
- Contagem de passos e notação $O$, $\Omega$, $\Theta$ (aula de Introdução)

------

## Motivação

Na Introdução, criamos agregados com `struct` e métodos, e vimos deduções de tipos primitivos em C ou C++ com `auto`. 
Nesta aula, veremos que:

- um **Tipo Abstrato de Dados** (TAD) é definido pelo que ele **faz** e pelo que ele **promete**, e não por como foi implementado
- um mesmo TAD pode ter **várias implementações**, cada uma pagando seus custos em operações diferentes (o **modelo de custos**)
- em C/C++, os **conceitos** (`concept`) descrevem um TAD diretamente no código (ou *Protocol* em Python)
- uma **Vista** (ou Vista de Vetor) é um TAD que **não é dono** dos dados, e é a forma como receberemos vetores nos algoritmos de **ordenação**, evitando ponteiros desnecessários

**Importante:** na Introdução, vimos que em C++ é possível incluir rotinas dentro de agregados (`struct`), que automaticamente são organizados como ponteiros de função. Em C puro isso precisa ser feito manualmente, ou usar funções livres globais. Nesse curso, adotamos essa estratégia dos métodos de C++, mas é sempre possível converter para uma solução puro C, caso necessário (*com alguns ponteiros a mais*, justo o que nós evitamos!).

------

## Tipo Abstrato de Dados (TAD)

Um *Tipo Abstrato de Dados* (TAD), do inglês *Abstract Data Type* -- ADT, é composto por:

1. um **modelo de dados**: os valores que o tipo representa (em C/C++, um agregado `struct`)
2. um conjunto de **operações** sobre esses dados (em C/C++, os métodos)
3. um **contrato**: as **invariantes** (o que é sempre verdade sobre os dados) e as **pré** e **pós-condições** de cada operação

- O usuário de um TAD (chamado *cliente*) só conhece as operações e o contrato: os detalhes internos são da **implementação**.
    * No curso, todo TAD poderá ter duas funções extras, chamadas `cria()` e `libera()`, para inicializar os dados e finalizar a memória corretamente.

**Exemplo cotidiano:** você usa um elevador apertando botões (operações), confiando que ele não abre a porta entre andares (invariante). Não precisa saber como é o motor!

# Parte 1: TAD Racional

------

## TAD Racional

Um número *racional* é uma fração $\frac{a}{b}$, com $a, b$ inteiros e $b \neq 0$.

**Operações** do TAD Racional:

- `soma(r)`: devolve um **novo** racional, com $\frac{a}{b} + \frac{c}{d} = \frac{ad + cb}{bd}$
- `multiplica(r)`: devolve um **novo** racional, com $\frac{a}{b} \cdot \frac{c}{d} = \frac{ac}{bd}$
- `igual(r)`: verdadeiro se representam o **mesmo número** (note que $\frac{1}{2} = \frac{2}{4}$)
- `imprime()`: imprime na forma reduzida/canônica, como `1/2`

Além disso, um método `cria(n, d)` inicializa o racional $\frac{n}{d}$ (pré-condição: $d \neq 0$)

**Desafio:** $\frac{1}{2}$ e $\frac{2}{4}$ são o mesmo racional? E o mesmo **agregado**?

. . .

O modelo de dados é simples (`int num, den;`), mas **onde reduzir a fração** é uma decisão de implementação!

------

## Algoritmo: Máximo Divisor Comum (Euclides)

Para reduzir $\frac{a}{b}$, dividimos ambos por $mdc(a, b)$. O algoritmo de Euclides usa $mdc(a, b) = mdc(b, a \bmod b)$:

::: -

:::::::::: ||

::::: |{50%}

```.cpp
int mdc(int a, int b) {
   while (b != 0) {
      int r = a % b;
      a = b;
      b = r;
   }
   return a < 0 ? -a : a;  // sempre >= 0
}
```

:::::

::::: |{45%}

```
mdc(84, 36):
   a=84  b=36  r=12
   a=36  b=12  r=0
   a=12  b=0   -> 12

84/36 = (84/12)/(36/12) = 7/3
```

:::::

::::::::::

:::

**Custo:** depende do tamanho dos números a e b, não entraremos em detalhes agora! É barato, mas **não** é $O(1)$!

------

## Implementação 1: Forma Canônica (Parte 1/2)

**Ideia:** reduzir **sempre**, em `cria`. Como `soma` e `multiplica` criam seus resultados com `cria`, todo racional fica reduzido.

::: -

:::::::::: ||

::::: |{55%}

```.cpp
struct Racional1 {
   int num, den;  // inv: den > 0, mdc(num,den) == 1
   void cria(int n, int d) {   // pre: d != 0
      int g = mdc(n, d);
      if (d < 0) g = -g;       // sinal no numerador
      num = n / g;
      den = d / g;
   }
   Racional1 soma(Racional1 r) { ... }
   Racional1 multiplica(Racional1 r) { ... }
   bool igual(Racional1 r) { ... }
   void imprime() { println("{}/{}", num, den); }
};
```

:::::

::::: |{40%}


:::::

::::::::::

:::



## Implementação 1: Forma Canônica (Parte 2/2)

**Ideia:** reduzir **sempre**, em `cria`. Como `soma` e `multiplica` criam seus resultados com `cria`, todo racional fica reduzido.

::: -

:::::::::: ||

::::: |{55%}

```.cpp
struct Racional1 {
   // ...
   Racional1 soma(Racional1 r) {
      Racional1 s;
      s.cria(num * r.den + r.num * den, den * r.den);
      return s;
   }
   Racional1 multiplica(Racional1 r) {
      Racional1 m;
      m.cria(num * r.num, den * r.den);
      return m;
   }
   bool igual(Racional1 r) { return num == r.num && den == r.den; }
   void imprime() { println("{}/{}", num, den); }
};
```

:::::

::::: |{40%}

**Invariante forte:** existe **uma única** representação para cada número (forma canônica).

Por isso, `igual` é só comparar campos, e `imprime` não precisa reduzir.

Em troca, **toda** criação paga um `mdc`.

:::::

::::::::::

:::

------

## Implementação 2: Forma Preguiçosa (Parte 1/2)

**Ideia:** **nunca** reduzir nas operações aritméticas. Só reduzimos quando for inevitável (na impressão).

::: -

:::::::::: ||

::::: |{55%}

```.cpp
struct Racional2 {
   int num, den;  // inv: den != 0 (só isso!)
   void cria(int n, int d) {   // pre: d != 0
      num = n;
      den = d;
   }
   Racional2 soma(Racional2 r) { ...  }
   Racional2 multiplica(Racional2 r) { ...   }
   bool igual(Racional2 r) {  ...   }
   void imprime() { ...  }
};
```

:::::

::::: |{40%}


:::::

::::::::::

:::


## Implementação 2: Forma Preguiçosa (Parte 2/2)

**Ideia:** **nunca** reduzir nas operações aritméticas. Só reduzimos quando for inevitável (na impressão).

::: -

:::::::::: ||

::::: |{55%}

```.cpp
struct Racional2 {
   // ...
   Racional2 soma(Racional2 r) {
      return {num * r.den + r.num * den, den * r.den};
   }
   Racional2 multiplica(Racional2 r) {
      return {num * r.num, den * r.den};
   }
   bool igual(Racional2 r) { return num * r.den == r.num * den; }
   void imprime() {
      int g = mdc(num, den);
      if (den < 0) g = -g;
      println("{}/{}", num / g, den / g);
   }
};
```

:::::

::::: |{40%}

**Invariante fraca:** $\frac{1}{2}$ e $\frac{2}{4}$ convivem como agregados diferentes.

Por isso, `igual` não pode comparar campos: usa $ad = cb$.

Em troca, `cria`, `soma` e `multiplica` ficam **sem nenhum** `mdc`.

:::::

::::::::::

:::


------

## Exemplo de Uso

O código cliente é **idêntico** para as duas implementações:

::: -

:::::::::: ||

::::: |{50%}

```.cpp
Racional1 a, b;
a.cria(1, 2);
b.cria(2, 4);
println("{}", a.igual(b));   // true
a.soma(b).imprime();         // 1/1
a.multiplica(b).imprime();   // 1/4
```

:::::

::::: |{45%}

```.cpp
Racional2 a, b;
a.cria(1, 2);
b.cria(2, 4);
println("{}", a.igual(b));   // true
a.soma(b).imprime();         // 1/1
a.multiplica(b).imprime();   // 1/4
```

:::::

::::::::::

:::

Na memória, porém, os agregados são diferentes:

```
Racional1 b:  | num: 1 | den: 2 |     (reduzido em cria)
Racional2 b:  | num: 2 | den: 4 |     (guardado como veio)
```

**Observação:** o TAD Racional não carrega recursos dinâmicos, então não precisa de `libera()`. Os TADs que alocarem memória (como as Pilhas) terão `cria()` **e** `libera()`.

# Parte 2: Conceitos em C++

-------

## Conceitos I

C++ permite definir *conceitos* (ou *concepts*). Esse recurso permite *definições genéricas* sobre algum tipo, exigindo, por exemplo, que um agregado possua certos métodos.
Exemplo prático para o TAD Racional (não incluímos o `cria()` e `libera()`):

```.cpp
template <typename R>
concept RacionalTAD = requires(R a, R b, int n, int d) {
   { a.soma(b) }       -> std::same_as<R>;   // devolve outro R
   { a.multiplica(b) } -> std::same_as<R>;
   { a.igual(b) }      -> std::same_as<bool>;
   { a.imprime() };
};
```

O `requires` lista **expressões** que precisam compilar, e a seta `->` restringe o tipo do resultado.

-------

## Conceitos II

Uma forma de validação de tipos em *tempo de compilação* é o `static_assert`. Como garantir que as duas implementações satisfazem o TAD?

```.cpp
static_assert(RacionalTAD<Racional1>);
static_assert(RacionalTAD<Racional2>);
// static_assert(RacionalTAD<int>);  // ERRO: int não tem 'soma'
```

Também podemos usar um conceito no lugar de um tipo automático, restringindo o `auto`:

```.cpp
auto             r1 = Racional1{};   // tipo automático
RacionalTAD auto r2 = Racional2{};   // tipo conceitual
Racional1        r3 = Racional1{};   // tipo explícito
// RacionalTAD auto r4 = 3.14;       // ERRO de compilação
```

-------

## Algoritmos Genéricos sobre um TAD

Com o conceito, escrevemos o algoritmo **uma vez**, para **qualquer** implementação. Exemplo: o número harmônico $H_n = \frac{1}{1} + \frac{1}{2} + \cdots + \frac{1}{n}$.

::: -

:::::::::: ||

::::: |{55%}

```.cpp
template <RacionalTAD R>
R harmonico(int n) {
   R h;
   h.cria(0, 1);
   for (int k = 1; k <= n; k++) {
      R t;
      t.cria(1, k);
      h = h.soma(t);
   }
   return h;
}
```

:::::

::::: |{40%}

```.cpp
// Exemplo de uso
harmonico<Racional1>(10).imprime();
// 7381/2520
harmonico<Racional2>(10).imprime();
// 7381/2520
```

:::::

::::::::::

:::

O algoritmo **não sabe** (e nem precisa saber) quando a fração é reduzida.

**Desafio:** aumente $n$. Qual das duas versões imprime um valor errado primeiro? Por quê?

-------

## Conceitos verificam Sintaxe, não Semântica

O conceito verifica **quais operações existem e com que tipos**, mas **não** verifica o contrato:

```.cpp
struct RacionalErrado {
   int num, den;
   void cria(int n, int d) { num = n; den = d; }
   RacionalErrado soma(RacionalErrado r) {         // subtrai!
      return {num * r.den - r.num * den, den * r.den};
   }
   RacionalErrado multiplica(RacionalErrado r) { return *this; }
   bool igual(RacionalErrado r) { return true; }
   void imprime() { println("?"); }
};
static_assert(RacionalTAD<RacionalErrado>);  // passa!
```

Nenhum `static_assert` percebe que `soma` subtrai, ou que `igual` mente. Para a **semântica**, usamos **testes** e **contratos** (`pre` e `post`).

# Parte 3: Modelos de Custo

-------

## Modelo de Custos de um TAD

O mesmo TAD, duas implementações, custos **distribuídos de forma diferente** ($L$: número de dígitos dos valores envolvidos):

::: -

| operação | Racional1 (canônica) | Racional2 (preguiçosa) |
|---|---|---|
| `cria` | $O(L)$ (um `mdc`) | $O(1)$ |
| `soma` | $O(L)$ | $O(1)$ |
| `multiplica` | $O(L)$ | $O(1)$ |
| `igual` | $O(1)$ | $O(1)$ (produto cruzado) |
| `imprime` | $O(1)$ | $O(L)$ (um `mdc`) |
| tamanho de `num`, `den` | mínimo possível | **cresce** a cada operação |

:::

Um **modelo de custos** é a tabela com o custo de **cada operação** de uma implementação. Nenhuma linha sozinha diz qual implementação é melhor: é um **balanço**.

**Pergunta:** se um programa faz milhões de somas e só imprime o resultado no fim, qual você escolheria? E se compara racionais o tempo todo?

-------

## O Custo Escondido: o Tamanho dos Números

No modelo RAM (aula de Introdução), uma operação aritmética custa um passo **porque o dado tem tamanho fixo**. A Racional2 viola essa hipótese silenciosamente:

```
H_n com Racional2 (sem reduzir):  den = 1 * 2 * 3 * ... * n = n!
H_n com Racional1 (reduzindo):    den divide mmc(1, 2, ..., n)
```

- $13! \approx 6{,}2 \times 10^9$ já **não cabe** em um `int` de 32 bits (*overflow*)
- `igual` faz produtos cruzados ($ad$ e $cb$), que estouram **ainda antes**
- reduzir sempre mantém os números pequenos, e é isso que o `mdc` "compra"

***Importante:*** *o modelo de custos precisa incluir o que a implementação faz com os **dados**, e não só quantos passos executa. Uma operação $O(1)$ que produz resultado errado não é rápida, é apenas errada.*

**Desafio**: para resolver isso, implemente um *BigNum* (números gigantes ilimitados em vetores).

# Parte 4: Vistas e SpanInt

-------

## Motivação: como receber um vetor?

Para escrever um algoritmo sobre um vetor, em C passamos **ponteiro e tamanho** separados:

```.cpp
int soma(int* v, int n);      // e se alguém passar o 'n' errado?
soma(a + 2, 3);               // aritmética de ponteiros exposta ao cliente
```

O ponteiro e o tamanho só fazem sentido **juntos**. Isso pede um TAD!

Queremos um agregado leve que:

- guarde **onde** os dados começam e **quantos** são
- permita **ler** e **alterar** a posição `i`
- **não seja dono** dos dados: o vetor original continua existindo, e as alterações aparecem nele

Esse tipo de TAD é chamado de **Vista** (do inglês *View*).

**Importante:** como boa prática de programação, evitaremos a passagem de ponteiros em parâmetros de funções.

-------

## O TAD `SpanInt`

Um `SpanInt` representa um trecho de vetor de `int` (sem posse), com os métodos `tamanho()`, `le(i)`, `altera(i, v)` e `fatia(a, b)`, que retorna outro `SpanInt` com os elementos de `a` até `b-1` (como o *slice* `v[a:b]` em Python).

::: -

:::::::::: ||

::::: |{55%}

```.cpp
struct SpanInt {
  int* inicio;  // primeiro elemento
  int  n;       // número de elementos
  int  tamanho()            { return n; }
  int  le(int i)            { return inicio[i]; }
  void altera(int i, int v) { inicio[i] = v; }
  // pre: 0 <= a <= b <= n
  SpanInt fatia(int a, int b) {
    return {.inicio = inicio + a, .n = b - a};
  }
};  // le e altera: pre(0 <= i < n)
```

:::::

::::: |{40%}

```.cpp
int v[] = {10, 20, 30, 40, 50};
SpanInt s{.inicio = v, .n = 5};
SpanInt meio = s.fatia(1, 4);
// meio: {20, 30, 40}
meio.altera(0, 99);
println("{}", v[1]); // 99 (sem cópia!)

int soma(SpanInt s) {  // recursiva!
   if (s.tamanho() == 0) return 0;
   return s.le(0) +
      soma(s.fatia(1, s.tamanho()));
}
```

:::::

::::::::::

:::

**Importante:** a aritmética de ponteiros (`inicio + a`) fica escondida **dentro** do TAD.

-------

## Conceito: Vista

Uma *Vista* (do inglês *View*) é um TAD que **referencia** um valor guardado em outro lugar (a *origem*), com três propriedades:
**não-posse:** alterações na origem são percebidas pela vista; **leve:** custo constante $O(1)$; **validade:** dura enquanto a origem existir.

::: -

:::::::::: ||

::::: |{50%}

```.cpp
template <typename V>
concept VistaTAD = requires(V v) {
   typename V::Tipo;   // tipo associado
   { v.le() };         // leitura origem
};

struct VistaInt {
   using Tipo = int;   // tipo associado
   const Tipo* origem; // não muda origem
   Tipo le() { return *origem; }
};
static_assert(VistaTAD<VistaInt>);
```

:::::

::::: |{45%}

```.cpp
// Exemplo de uso
int x = 10;
VistaInt y{.origem = &x};
println("{}", y.le()); // 10

x = 30;
println("{}", y.le()); // 30 (não-posse)
```

:::::

::::::::::

:::

**Desafio:** por que `origem` é do tipo `const int*` e não `int*`?

-------

## Conceito: Vista Mutável

Uma *Vista Mutável* é uma Vista que também possui `altera(v)`, que modifica o valor **na origem**.

::: -

:::::::::: ||

::::: |{50%}

```.cpp
template <typename V>
concept VistaMutavelTAD = VistaTAD<V> &&
   requires(V v, typename V::Tipo t) {
   { v.altera(t) };  // escrita na origem
};

struct VistaMutavelInt {
   using Tipo = int;  // tipo associado
   Tipo* origem;
   Tipo  le()          { return *origem; }
   void altera(Tipo v) { *origem = v; }
};
static_assert(VistaMutavelTAD<VistaMutavelInt>);
```

:::::

::::: |{45%}

```.cpp
// Exemplo de uso
int x = 10;
VistaMutavelInt y{.origem = &x};

y.altera(20);
println("{}", x);      // 20

x = 30;
println("{}", y.le()); // 30 (não-posse)
```

:::::

::::::::::

:::

**Desafio:** `VistaMutavelInt` satisfaz `VistaTAD`? E `VistaInt` satisfaz `VistaMutavelTAD`?

------

## Conceito: Vista (Mutável) de Vetor

A interface de uma vista de vetor, escrita como conceito:

::: -

:::::::::: ||

::::: |{55%}

```.cpp
template <typename V, typename T>
concept VistaVetorTAD = requires(V v, int i) {
   { v.tamanho() } -> std::same_as<int>;
   { v.le(i) }     -> std::same_as<T>;
};
template <typename V, typename T>
concept VistaMutavelVetorTAD =
   VistaVetorTAD<V, T> &&
   requires(V v, int i, T t) {
   { v.altera(i, t) };
};  // le e altera: pre(0 <= i < tamanho())

static_assert(VistaMutavelVetorTAD<SpanInt, int>);
```

:::::

::::: |{40%}

```.cpp
// troca dois elementos, na origem
void troca(
   VistaMutavelVetorTAD<int> auto v,
   int i, int j) {
   int t = v.le(i);
   v.altera(i, v.le(j));
   v.altera(j, t);
}
// Exemplo de uso
int a[] = {1, 2, 3};
SpanInt s{.inicio = a, .n = 3};
troca(s, 0, 2);       // cópia leve
println("{} {} {}",
   a[0], a[1], a[2]); // 3 2 1
```

:::::

::::::::::

:::

**Importante:** a vista é passada **por valor** (copia só um ponteiro e um `int`!), mas `altera` muda o vetor **original**. Note que `fatia` **não** é exigida: nem toda vista precisa sabê-la.

# Parte 5: Ordenação sobre Vistas

-------

## O Problema da Ordenação

**Problema:** dado um span `v` com `n` elementos, rearranjá-los em ordem crescente.

O contrato de toda função `ordena(v)`:

- **pré-condição:** nenhuma (qualquer vetor pode ser ordenado)
- **pós-condição 1:** `v.le(0) <= v.le(1) <= ... <= v.le(n-1)`
- **pós-condição 2:** os elementos são uma **permutação** dos originais (nada se perde, nada se cria)

**Desafio:** escreva um "ordena" que satisfaça a pós-condição 1 e viole a 2. É fácil?

. . .

*Basta `for (i...) v.altera(i, 0);`. Por isso as duas condições são necessárias!*

Veremos três algoritmos clássicos, todos usando **apenas** a interface da vista: `tamanho`, `le` e `altera`.

-------

## Bubble Sort (bolha)

Já contamos os passos do Bubble Sort otimizado na Introdução. Agora, ele recebe uma **vista**:

::: -

:::::::::: ||

::::: |{55%}

```.cpp
void bubble_sort(SpanInt v) {
   for (int i = v.tamanho(); i > 0; i--) {
      bool trocou = false;
      for (int j = 0; j < i - 1; j++)
         if (v.le(j) > v.le(j + 1)) {
            troca(v, j, j + 1);
            trocou = true;
         }
      if (!trocou)
         break;  // já está ordenado!
   }
}
```

:::::

::::: |{40%}

```.cpp
// Exemplo de uso
int a[] = {5, 2, 4, 1, 3};
SpanInt s{.inicio = a, .n = 5};
bubble_sort(s);
// a: {1, 2, 3, 4, 5}

// ordena só o meio!
int b[] = {9, 5, 2, 4, 0};
bubble_sort(SpanInt{.inicio = b, .n = 5}
              .fatia(1, 4));
// b: {9, 2, 4, 5, 0}
```

:::::

::::::::::

:::

**Observação:** o algoritmo não sabe que existe um vetor maior: a vista **é** o seu vetor.

-------

## Selection Sort (seleção)

**Ideia:** selecione o **menor** elemento restante e coloque-o na posição `i`.

::: -

:::::::::: ||

::::: |{55%}

```.cpp
void selection_sort(SpanInt v) {
   int n = v.tamanho();
   for (int i = 0; i < n - 1; i++) {
      int menor = i;
      for (int j = i + 1; j < n; j++)
         if (v.le(j) < v.le(menor))
            menor = j;
      if (menor != i)
         troca(v, i, menor);
   }
}
```

:::::

::::: |{40%}

```
  i=0: | 1 | 2 | 4 | 5 | 3 |
  i=1: | 1 | 2 | 4 | 5 | 3 |
  i=2: | 1 | 2 | 3 | 5 | 4 |
  i=3: | 1 | 2 | 3 | 4 | 5 |
```

Vetor `{5, 2, 4, 1, 3}` ao fim de cada `i`: o **início** (à esquerda) já está ordenado e definitivo.

:::::

::::::::::

:::

- Comparações: sempre $\frac{n(n-1)}{2}$, ou seja, $\Theta(n^2)$ **em todo caso**
- Trocas: no máximo $n - 1$, ou seja, $O(n)$

-------

## Insertion Sort (inserção)

**Ideia:** mantenha `v[0..i-1]` ordenado e **insira** `v[i]` no lugar certo, deslocando os maiores para a direita.

::: -

:::::::::: ||

::::: |{55%}

```.cpp
void insertion_sort(SpanInt v) {
   for (int i = 1; i < v.tamanho(); i++) {
      int x = v.le(i);
      int j = i - 1;
      while (j >= 0 && v.le(j) > x) {
         v.altera(j + 1, v.le(j)); // desloca
         j--;
      }
      v.altera(j + 1, x);          // encaixa
   }
}
```

:::::

::::: |{40%}

```
  i=1: | 2 | 5 | 4 | 1 | 3 |
  i=2: | 2 | 4 | 5 | 1 | 3 |
  i=3: | 1 | 2 | 4 | 5 | 3 |
  i=4: | 1 | 2 | 3 | 4 | 5 |
```

Vetor `{5, 2, 4, 1, 3}` ao fim de cada `i`: o início está ordenado, mas **não** é definitivo.

:::::

::::::::::

:::

- Pior caso (decrescente) $\Theta(n^2)$; **melhor caso** (já ordenado) $\Theta(n)$
- Excelente para $n$ pequeno ou vetores *quase* ordenados

-------

## Modelo de Custos da Ordenação

Na Introdução, contamos **linhas**. Mas, assim como no Racional, o que importa depende do que é **caro**: ler (comparar) ou escrever?

::: -

| algoritmo | `le` (melhor) | `le` (pior) | `altera` (melhor) | `altera` (pior) |
|---|---|---|---|---|
| Bubble (otimizado) | $\Theta(n)$ | $\Theta(n^2)$ | $0$ | $\Theta(n^2)$ |
| Selection | $\Theta(n^2)$ | $\Theta(n^2)$ | $0$ | $\Theta(n)$ |
| Insertion | $\Theta(n)$ | $\Theta(n^2)$ | $\Theta(n)$ | $\Theta(n^2)$ |

:::

- se **escrever é caro** (elementos grandes, memória *flash*, disco remoto): **Selection**
- se o vetor está **quase ordenado**: **Insertion** (ou Bubble otimizado)
- assintoticamente, no pior caso, os três são $\Theta(n^2)$: o modelo de custos é que os diferencia

-------

## Exercício Prático: Medindo Custos com uma Vista Contadora

Altere os parâmetros dos métodos de ordenação para receber não um `SpanInt`, mas um `VistaMutavelVetorTAD<int>`.
Com isso, é fácil monitorar o número de passos **real** que o algoritmo executa!

::: -

:::::::::: ||

::::: |{55%}

```.cpp
struct VistaContadora {
   SpanInt         s;
   VistaMutavelInt leituras;  // contadores na origem
   VistaMutavelInt escritas;  // (não-posse!)
   int tamanho() { return s.tamanho(); }
   int le(int i) {
      leituras.altera(leituras.le() + 1);
      return s.le(i);
   }
   void altera(int i, int v) {
      escritas.altera(escritas.le() + 1);
      s.altera(i, v);
   }
};
static_assert(
   VistaMutavelVetorTAD<VistaContadora, int>);
```

:::::

::::: |{40%}

```.cpp
// Exemplo de uso
int a[] = {5, 4, 3, 2, 1};
int nle = 0, nalt = 0;
selection_sort(VistaContadora{
   .s        = SpanInt{.inicio = a, .n = 5},
   .leituras = VistaMutavelInt{.origem = &nle},
   .escritas = VistaMutavelInt{.origem = &nalt}});
println("le={} altera={}", nle, nalt);
// le=44 altera=4
```

:::::

::::::::::

:::

**Desafio:** por que `leituras` é uma `VistaMutavelInt`, e não um simples `int`? (Lembre que a vista é passada **por valor**, inclusive para `troca`!)

-------

## Exercício: Preencha o Modelo de Custos

Use a `VistaContadora` para preencher a tabela, com $n = 1000$:

::: -

| entrada | Bubble (`le` / `altera`) | Selection (`le` / `altera`) | Insertion (`le` / `altera`) |
|---|---|---|---|
| já ordenado | | | |
| decrescente | | | |
| aleatório | | | |

:::

1. Os números conferem com a tabela de $\Theta$ do slide anterior?
2. Dobre $n$ para $2000$. Quais colunas **quadruplicam**? Quais só **dobram**?
3. Qual algoritmo você usaria se cada `altera` custasse 100 vezes mais que um `le`?

-------

## Ordenação na Biblioteca Padrão (C++ STL)

Na STL, o `std::span` (que vimos na Introdução) cumpre o papel do nosso `SpanInt`, e o `std::ranges::sort` ordena qualquer vista:

```.cpp
import std;

int main() {
   int b[] = {9, 5, 2, 4, 0};
   std::span<int> s{b};
   std::ranges::sort(s.subspan(1, 3));       // como nossa fatia(1, 4)
   println("{}", b);                         // [9, 2, 4, 5, 0]
   std::ranges::sort(s);                     // O(n log n)
   println("{}", std::ranges::is_sorted(s)); // true
   return 0;
}
```

**Importante:** nesse curso é permitido o uso de TADs e algoritmos prontos da STL, *desde que você **saiba seu modelo de custos***!

**Mais adiante:** veremos algoritmos $O(n \log n)$ (Merge Sort e Quick Sort), que usam **divisão e conquista**, e para isso a operação `fatia` será essencial.

-------

## TAD, Vistas e Ordenação: Revisão Geral

- O que compõe um TAD? Qual a diferença entre interface e implementação?
- O que é uma invariante? Qual a invariante de `Racional1`? E de `Racional2`?
- Por que `igual` é diferente nas duas implementações do Racional?
- O que é um modelo de custos? Por que nenhuma implementação do Racional é "a melhor"?
- O que um conceito (`concept`) verifica? O que ele **não** verifica?
- Por que uma Vista pode ser passada por valor e, mesmo assim, alterar a origem?
- Qual algoritmo de ordenação faz menos escritas? E qual é melhor para vetores quase ordenados?

**Próxima aula:** a **Pilha**, nosso primeiro TAD com **duas implementações** (sequencial e encadeada), e seu modelo de custos!

-------

## Exercícios

1. Acrescente ao TAD Racional a operação `menor(r)`, nas duas implementações. Qual o custo em cada uma? (Cuidado com o sinal do denominador na `Racional2`!)
2. Crie uma `Racional3` híbrida, que reduz apenas quando `|den|` passa de um limite. Ela satisfaz `RacionalTAD`? Monte o seu modelo de custos.
3. Escreva `bool ordenado(VistaVetorTAD<int> auto v)`, que verifica a pós-condição 1 da ordenação. Note que ela só precisa da vista **não-mutável**!
4. Escreva uma vista `SpanInvertido`, que lê o `SpanInt` de trás para frente. O que acontece se você ordenar com ela?
5. Escreva `soma` recursiva **sem** `fatia`, usando apenas `VistaVetorTAD`. O que precisou mudar?

---------

## Bibliografia Recomendada

Além da bibliografia do curso, recomendamos para esse tópico:

- Szwarcfiter, J.L; Markenzon, L. Estruturas de Dados e seus Algoritmos. Rio de Janeiro, LTC, 1994.

Bibliografia Adicional:

- Cerqueira, R.; Celes, W.; Rangel, J.L. Introdução a estruturas de dados: com técnicas de programação em C. Editora, 2004.
- Knuth, D.E. The Art of Computer Programming - Vol II (Seção 4.5.1: Frações). 3rd Edition. Addison Wesley, 1997.
- Sedgewick, R.; Wayne, K. Algorithms, 4th Edition. Addison-Wesley, 2011.
- Livro "The C++ Programming Language" de Bjarne Stroustrup
- Dicas e normas C++: https://github.com/isocpp/CppCoreGuidelines

# Agradecimentos

-----

## Pessoas

Em especial, agradeço aos colegas que elaboraram bons materiais, como o prof. Fabiano Oliveira (IME-UERJ), e o prof. Jayme Szwarcfiter cujos conceitos formam o cerne desses slides.

Estendo os agradecimentos aos demais colegas que colaboraram com a elaboração do material do curso de [Pesquisa Operacional](https://github.com/igormcoelho/curso-pesquisa-operacional-i), que abriu caminho para verificação prática dessa tecnologia de slides.

-----

## Software

Esse material de curso só é possível graças aos inúmeros projetos de código-aberto que são necessários a ele, incluindo:

- pandoc
- LaTeX
- GNU/Linux
- git
- markdown-preview-enhanced (github)
- visual studio code
- atom
- revealjs
- groomit-mpx (screen drawing tool)
- xournal (screen drawing tool)
- ...

-----

## Empresas

Agradecimento especial a empresas que suportam projetos livres envolvidos nesse curso:

- github
- gitlab
- microsoft
- google
- ...

-----

## Reprodução do material

Esses slides foram escritos utilizando pandoc, segundo o tutorial ilectures:

- https://igormcoelho.github.io/ilectures-pandoc/

Exceto expressamente mencionado (com as devidas ressalvas ao material cedido por colegas), a licença será Creative Commons.

**Licença:** CC-BY 4.0 2020

Igor Machado Coelho

-------

## This Slide Is Intentionally Blank (for goomit-mpx)