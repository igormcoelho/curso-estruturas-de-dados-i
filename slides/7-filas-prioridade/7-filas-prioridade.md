---
author: Igor Machado Coelho
title: Estruturas de Dados I
subtitle: Filas de Prioridade
date: 14/10/2020
transition: cube
fontsize: 10
header-includes:
- <link rel="stylesheet" type="text/css" href="general.css">
- <link rel="stylesheet" type="text/css" href="reveal-beamer.css">
---




# Filas de Prioridade

------

## Pré-Requisitos

São requisitos para essa aula:

- Introdução/Fundamentos de Programação (em alguma linguagem de programação)
- Interesse em aprender C/C++
- Noções de tipos de dados
- Noções de listas e encadeamento
- Aula de filas
- Aula de árvores


# Tipo Abstrato: Fila de Prioridade

------

## Fila de Prioridade

A Fila de Prioridade (do inglês *Priority Queue*) é um Tipo Abstrato de Dado (TAD) que opera de forma similar a uma Fila.

Lembramos que o TAD Fila tem comportamento FIFO (*first-in first-out*), onde o elemento de *maior prioridade para sair da fila* é o elemento que *entrou primeiro na fila*.

O conceito de *prioridade* é explicitado  nas Filas de Prioridade através de um *valor numérico*. Nesse caso, a lógica de prioridade pode operar pelo *menor* ou pelo *maior* valor, dependendo da aplicação.

-------

## Filas de Prioridade na Computação

Filas de Prioridade são estruturas fundamentais na própria computação.
Também são úteis na implementações de algoritmos em grafos, como a busca por *árvores geradoras mínimas* (aulas futuras).


Por exemplo, quando se envia pacotes de dados a roteadores, existem mecanismos que podem tirar vantagem de *valores de prioridade* entre pacotes (dados de voz e de download, etc). Uma interpretação cotidiana poderia ser uma *fila prioritária por idade*, na qual os indivíduos *mais velhos* seriam sempre atendidos antes dos *mais novos*.


![Fila de Prioridade - CC BY 3.0 - thenounproject.com](2020-09-18-20-06-17.png){width=20%}


--------

## Operações de uma Fila de Prioridade

Uma Fila de Prioridade é uma estrutura de dados com uma *direção pre-definida* (vamos assumir *maior prioridade* para o *menor valor*), consistindo de 3 operações básicas:

- frente "mais prioritária" (*peek min* ou *find min*)
- enfileira (*enqueue*, *push* ou *insert*)
- desenfileira "mais prioritário" (*dequeue min*, *pop min* ou *extract min*)

As operações trabalham com *chaves numéricas* e, opcionalmente, um conteúdo atrelado a cada chave.
Outra operação comum no TAD, embora considerada uma *operação interna*, é a de *redução de chave* (*decrease key*).

--------

## Implementações

A implementação do TAD Fila de Prioridade geralmente se dá através de uma *árvores de prioridade* denominada *heap*. O heap (ou *min heap*) é uma *árvore binária completa* com a seguinte propriedade:

- se $x$ é pai de $y$, então $x \leq y$

![Min-Heap. Créditos: Fabiano Oliveira](2020-10-14-16-39-35.png){width=70%}

-------

## Definição do *Conceito* Fila de Prioridade em C++

O *conceito* de fila de prioridade somente requer suas três operações básicas. Como consideramos uma *fila de prioridade genérica* (fila de inteiro, char, etc), definimos um *conceito genérico* chamado `FilaPrioridadeTAD`:

```{.cpp}
template<typename Agregado, typename Tipo>
concept bool
FilaPrioridadeTAD = requires(Agregado a, Tipo t)
{
   // requer operação 'frente' mais prioritária 
   { a.frente() };
   // requer operação 'insere' sobre tipo 't'
   { a.insere(t) };
   // requer operação 'remove' mais prioritário
   { a.remove() };
};
```
Note que o tipo genérico pode ser estendido para comportar um elemento interno, além da chave numérica.


# Implementação *heap*

--------

## Implementação *heap* com vetor

Apesar de sua estrutura de árvore, podemos representá-la eficientemente com um vetor, numa implementação puramente sequencial.

![](2020-10-14-16-39-35.png){width=70%}

Representação por níveis (*árvore completa*):
```
| 3 | 10 | 7 | 11 | 19 | 35 | 8 | 14 | 12 | 22 | 30 | 44 |
```

Assim, os dados sempre estarão em um *espaço contíguo* de memória.

-------

## Implementação Heap1


Consideraremos uma fila sequencial com, no máximo, `MAXN` elementos do tipo caractere.

```{.cpp}
constexpr int MAX_N = 50; // capacidade máxima da fila
class Heap1
{
public:
  int elementos [MAXN];      // elementos na fila
  int N;                     // num. de elementos na fila
  void cria () { ... }       // inicializa agregado
  void libera () { ... }     // finaliza agregado
  int frente () { ... }
  void insere (int chave){ ... }
  int remove () { ... }
};
// verifica se agregado Heap1 satisfaz conceito FilaPrioridadeTAD
static_assert(FilaPrioridadeTAD<Heap1, int>);
```

-------

## Utilização do Heap

Antes de completar as funções pendentes, utilizaremos a `Heap1`:

```{.cpp}
int main () {
   Heap1 h;
   h.cria();
   h.insere(20);
   h.insere(10);
   h.insere(30);
   printf("%c\n", h.frente());      
   printf("%c\n", h.remove());  
   h.insere(25);
   while(p.N > 0)
      printf("%c\n", h.remove());
   h.libera();
   return 0;
}
```
***Verifique as impressões em tela:*** *10 10 20 25 30*

---------

## Implementação Heap1 - cria/libera

A operação `cria` inicializa a fila para uso, e a função `libera` desaloca os recursos dinâmicos.

```{.cpp}
class Heap1 {
...
void cria() {
   this->N = 0;
}

void libera() {
   // nenhum recurso dinâmico para desalocar
}
...
}
```
---------


## Algoritmo Heap1 *frente* 

A operação `frente` retorna o elemento mais prioritário do heap.
Felizmente, ele sempre será a raiz da árvore!

![](2020-10-14-16-39-35.png){width=70%}

Representação por níveis (*árvore completa*):
```
| 3 | 10 | 7 | 11 | 19 | 35 | 8 | 14 | 12 | 22 | 30 | 44 |
```

**Desafio**: verifique se é possível o elemento mais prioritário não estar na raiz do heap.

---------

## Algoritmo Heap1 *insere* - Parte 1/2

A operação `insere` em adiciona um novo elemento de acordo com sua prioridade.
Como manter a corretude das propriedades do heap?

**Exemplo:** como inserir o elemento $5$?

![](2020-10-14-16-39-35.png){width=70%}

Representação por níveis (*árvore completa*):
```
| 3 | 10 | 7 | 11 | 19 | 35 | 8 | 14 | 12 | 22 | 30 | 44 |
```

-------

## Algoritmo Heap1 *insere* - Parte 2/2

Para manter a corretude das propriedades do heap, em especial, de uma *árvore completa*, adicionamos o elemento na *última posição do vetor*.

**Exemplo:** como inserir o elemento $5$?

![](2020-10-14-16-39-35.png){width=30%}

Representação por níveis (*árvore completa*):
```
| 3 | 10 | 7 | 11 | 19 | 35 | 8 | 14 | 12 | 22 | 30 | 44 |
```

Como *corrigir* a árvore? **Solução:** trocas sucessivas *subindo* até a raiz.

```
|3| 10 | 7 | 11 | 19 | 35 | 8 | 14 | 12 | 22 | 30 | 44 |5|
|3| 10 | 7 | 11 | 19 | *5 | 8 | 14 | 12 | 22 | 30 | 44 |*35|
|3| 10 | *5 | 11 | 19 | *7 | 8 | 14 | 12 | 22 | 30 | 44 |*35|
```

-------


## Algoritmo Heap1 *remove* - Parte 1/2

A operação `remove` em adiciona um novo elemento de acordo com sua prioridade.
Como manter a corretude das propriedades do heap?

**Exemplo:** como remover o elemento $3$?

![](2020-10-14-16-39-35.png){width=70%}

Representação por níveis (*árvore completa*):
```
| 3 | 10 | 7 | 11 | 19 | 35 | 8 | 14 | 12 | 22 | 30 | 44 |
```

-------

## Algoritmo Heap1 *remove* - Parte 2/2

Para manter a corretude das propriedades do heap, em especial, de uma *árvore completa*, trocamos o *primeiro* com o *último* elemento do vetor.

**Exemplo:** como remover o elemento $3$?

![](2020-10-14-16-39-35.png){width=30%}

Representação por níveis (*árvore completa*):
```
| 3 | 10 | 7 | 11 | 19 | 35 | 8 | 14 | 12 | 22 | 30 | 44 |
```

Como *corrigir* a árvore? **Solução:** trocas sucessivas *descendo* até uma folha.

```
| 44 | 10 | 7 | 11 | 19 | 35 | 8 | 14 | 12 | 22 | 30 | 3 |
| *7 | 10 | *44 | 11 | 19 | 35 | 8 | 14 | 12 | 22 | 30 | 3 |
| *7 | 10 | *8 | 11 | 19 | 35 | *44 | 14 | 12 | 22 | 30 | 3 |
| *7 | 10 | *8 | 11 | 19 | 35 | *44 | 14 | 12 | 22 | 30 | x |
```

# Implementação Heap em C++



---------


## Bibliografia Recomendada


Além da bibliografia do curso, recomendamos para esse tópico:

- Szwarcfiter, J.L; Markenzon, L. Estruturas de Dados e seus Algoritmos. Rio de Janeiro, LTC, 1994.
Bibliografia Adicional:
- Cerqueira, R.; Celes, W.; Rangel, J.L. Introdução a estruturas de dados: com técnicas de programação em C. Editora, 2004.
- Cormen, T.H.; Leiserson, C.E.; Rivest, R.L.; Stein Algoritmos: Teoria e Prática. Ed. Campus, 2002.
- Cormen, T.H.; Leiserson, C.E.; Rivest, R.L.; Stein, C. Introduction to Algorithms, 3rd ed.. The MIT Press, 2009.
- Preiss, B.R. Estruturas de Dados e Algoritmos Ed. Campus, 2000;
- Knuth, D.E. The Art of Computer Programming - Vols I e III. 2nd Edition. Addison Wesley, 1973.
- Graham, R.L., Knuth, D.E., Patashnik, O. Matemática Concreta. Segunda Edição, Rio de Janeiro, LTC, 1995.
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
