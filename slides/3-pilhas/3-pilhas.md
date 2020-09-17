---
author: Igor Machado Coelho
title: Estruturas de Dados I
subtitle: Pilhas
date: 16/09/2020
transition: linear
fontsize: 10
header-includes:
- <link rel="stylesheet" type="text/css" href="general.css">
- <link rel="stylesheet" type="text/css" href="reveal-beamer.css">
---





# Pilhas

------

## Pré-Requisitos

São requisitos para essa aula o conhecimento de:

- Introdução/Fundamentos de Programação (em alguma linguagem de programação)
- Interesse em aprender C/C++
- Noções de tipos de dados
- Noções de listas e encadeamento


# Tipo Abstrato: Pilha

------

## Pilha

A Pilha (do inglês *Stack*) é um Tipo Abstrato de Dado (TAD) que pode ser compreendida como vemos no cotidiano.

Em uma *pilha de pratos*, por exemplo:

- Só se consegue "inserir"
(empilhar) novos pratos no *topo* da pilha
- Só podemos "remover"
(desempilhar) os pratos do *topo* da pilha

![Pilhas](2020-09-16-17-29-00.png){width=50%}


-------

## Pilhas na computação

Pilhas são estruturas fundamentais na própria computação. 

Por exemplo, as chamadas de uma função recursiva podem ser feitas utilizando uma pilha!

*... e é precisamente desta maneira que o
sistema operacional consegue executar várias de suas funções internas!*

Linguagens de programação como Java, C# e Python são implementadas através de operações em pilhas.

--------

## Operações de uma Pilha

Uma Pilha é uma estrutura de dados linear (assim como estruturas de lista),
consistindo de 3 operações básicas: 

- topo
- empilhar (*push*)
- desempilhar (*pop*)


Seu comportamento é descrito como LIFO (last-in first-out), ou seja, o *último* elemento a entrar na pilha será o *primeiro* a sair.

--------

## Implementações

De forma geral, uma pilha pode ser implementada utilizando uma lista linear,
porém com acesso aos elementos restritos a uma única extremidade dessa lista.

$$ \rightleftarrows | \; 3 \; | \; 2 \; | \; 1 \; |$$


Para o TAD Pilha, estudaremos duas
formas distintas de implementação: Sequencial e Encadeada.


--------

## Definição do *Conceito* Pilha em C++

O *conceito* de pilha somente requer suas três operações básicas. Como consideramos uma *pilha genérica* (pilha de inteiro, char, etc), definimos um *conceito genérico* chamado `PilhaTAD`:

```{.cpp}
template<typename Agregado, typename Tipo>
concept bool
PilhaTAD = requires(Agregado a, Tipo t)
{
   // requer operação 'topo'
   { a.topo() };
   // requer operação 'empilha' sobre tipo 't'
   { a.empilha(t) };
   // requer operação 'desempilha'
   { a.desempilha() };
};
```

# Pilhas Sequenciais

--------

## Pilhas Sequenciais

As Pilhas Sequenciais utilizam um array para armazenar os dados. 
Assim, os dados sempre estarão em um *espaço contíguo* de memória.


-------

## Implementação


Consideraremos uma pilha sequencial com, no máximo, `MAXN` elementos do tipo caractere.

```{.cpp}
constexpr int MAXN = 100'000; // capacidade máxima da pilha
class PilhaSeq1
{
public:
  char elementos [MAXN];      // elementos na pilha
  int N;                      // num. de elementos na pilha
  void cria () { ... }        // inicializa agregado
  void libera () { ... }      // finaliza agregado
  char topo () { ... }
  void empilha (char dado){ ... };
  char desempilha () { ... };
};
// verifica se agregado PilhaSeq1 satisfaz conceito PilhaTAD
static_assert(PilhaTAD<PilhaSeq1, char>);
```

-------

## Utilização da Pilha

Antes de completar as funções pendentes, utilizaremos a `PilhaSeq1`:

```{.cpp}
int main () {
   PilhaSeq1 p;
   p.cria();
   p.empilha('A');
   p.empilha('B');
   p.empilha('C');
   printf("%c\n", p.topo());
   printf("%c\n", p.desempilha());
   p.empilha('D');
   while(p.N > 0)
      printf("%c\n", p.desempilha());
   p.libera();
   return 0;
}
``` 
***Verifique as impressões em tela:*** *C C D B A*

---------

## Implementação: Cria e Libera

A operação `cria` inicializa a pilha para uso, e a função `libera` desaloca os recursos dinâmicos.

```{.cpp}
class PilhaSeq1 {
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

## Implementação: Empilha / Desempilha

A operação `empilha` em uma pilha sequencial adiciona um novo elemento ao topo da pilha.
A operação `desempilha` em uma pilha sequencial remove e retorna o último elemento da pilha.

```{.cpp}
class PilhaSeq1 {
...
void empilha(char dado) {
   this->elementos[N] = dado;
   this->N++;                 // N = N + 1
}

char desempilha() {
   this->N--;                 // N = N - 1
   return elementos[N];
}
...
}
```

---------

## Implementação: Topo

A operação de topo em uma pilha sequencial retorna o último elemento empilhado.

```{.cpp}
class PilhaSeq1 {
...
char topo() {
   return this->elementos[N-1];
}
...
}
```

***Desafio:*** *O que aconteceria se a pilha estivesse vazia e o `topo()` fosse invocado? Como permitir que o programa continue mesmo após situações inesperadas como essa?*

***Dica:*** *Retorne um `char` **opcional**, com uma pequena modificação na função `topo()`. Exemplo:* `std::optional<char> topo() { ... }`.


-------

## Exemplo de uso

Considere uma pilha sequencial (`MAXN=5`):
`PilhaSeq1 p; p.cria();`

```
p.N: | 0 |     p.elementos: |   |   |   |   |   |   
                              0   1   2   3   4   
```

Agora, empilhamos `A`, `B` e `C`, e depois desempilhamos uma vez.

```
p.N: | 1 |     p.elementos: | A |   |   |   |   |   
                              0   1   2   3   4   
```

```
p.N: | 2 |     p.elementos: | A | B |   |   |   |   
                              0   1   2   3   4   
```

```
p.N: | 3 |     p.elementos: | A | B | C |   |   |   
                              0   1   2   3   4   
```

```
p.N: | 2 |     p.elementos: | A | B |   |   |   |   
                              0   1   2   3   4   
```

*Qual o topo atual da pilha?*

---------

## Análise Preliminar: Pilha Sequencial

A Pilha Sequencial tem a vantagem de ser bastante simples de implementar, ocupando um espaço constante (na memória) para todas operações.

Porém, existe a limitação física de `MAXN` posições imposta pela alocação estática, 
não permitindo que a pilha ultrapasse esse limite.

***Desafio:*** implemente uma Pilha Sequencial utilizando alocação dinâmica para o vetor `elementos`. 
Assim, quando não houver espaço
para novos elementos, aloque mais espaço na memória (copiando elementos existentes para o novo vetor).

***Dica:*** Experimente a estratégia de *dobrar a capacidade* da pilha (quando necessário), e reduzir à metade a capacidade (quando necessário). Essa estratégia é bastante eficiente, mas requer alteração nos métodos `cria`, `libera`, `empilha` e `desempilha`.

# Pilhas Encadeadas

--------

## Pilhas Encadeadas

A implementação do TAD Pilha pode ser feito através de uma *estrutura encadeada* com alocação dinâmica de memória.

A vantagem é não precisar pre-determinar uma capacidade máxima da pilha (o limite é a memória do computador!).
A desvantagem é depender de implementações ligeiramente mais complexas.


-------

## Implementação

Consideraremos uma pilha encadeada, utilizando um agregado `NoPilha1` para conectar cada elemento da pilha:

::::::::::{.columns}

:::::{.column width=33%}

```{.cpp}
class NoPilha1 
{
public:
   char dado;
   NoPilha1* prox;
};
```

:::::

:::::{.column  width=67%}

```{.cpp}
class PilhaEnc1
{
public:
  NoPilha1* inicio;
  int N;                      
  void cria () { ... }        
  void libera () { ... }     
  char topo () { ... }
  void empilha (char dado){ ... };
  char desempilha () { ... };
};
// verifica agregado PilhaEnc1
static_assert(PilhaTAD<PilhaEnc1, char>);
```

:::::

::::::::::


-------

## Exemplo de uso: `PilhaEnc1 p; p.cria();`

**p.N: 0  $\quad$  p.inicio: 0  $\quad$  $topo \leftarrow \epsilon$**

```
|     |     |     |     |     |     |     |     |     |     |    
   0     4    ...   100   104   108   112   116   ...   8GiB
```

*Agora, empilhamos `A` e `B`, depois desempilhamos uma vez.*


**p.N: 1  $\quad$  p.inicio: 112 $\quad$  $topo \leftarrow A$**

```
|     |     |     |     |     |     |  A  |  0  |     |     |    
   0     4    ...   100   104   108   112   116   ...   8GiB
```

**p.N: 2  $\quad$  p.inicio: 100 $\quad$  $topo \leftarrow B \leftarrow A$**

```
|     |     |     |  B  | 112 |     |  A  |  0  |     |     |    
   0     4    ...   100   104   108   112   116   ...   8GiB
```

**p.N: 1  $\quad$  p.inicio: 112 $\quad$  $topo \leftarrow A$**

```
|     |     |     |     |     |     |  A  |  0  |     |     |    
   0     4    ...   100   104   108   112   116   ...   8GiB
```

-------

## Implementação: Cria e Libera

```{.cpp}
class PilhaSeq1 {
...
void cria() {
   this->N = 0;      // zero elementos na pilha
   this->inicio = 0; // endereço zero de memória
}

void libera() {
   while (this->N > 0) {
      NoPilha1* p = this->inicio->prox;
      delete inicio;
      inicio = p;
      this->N--;     // N = N - 1
   }
}
...
}
```
---------




## Bibliografia Recomendada


Além da bibliografia do curso, recomendamos (para esse tópico):

- Livro "Introdução a estruturas de dados" de W. Celes e J. L. Rangel
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