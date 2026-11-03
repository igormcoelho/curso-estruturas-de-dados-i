## Estruturas de Dados I

Materiais gerais de Estruturas de Dados I do [Prof. Igor Machado Coelho](https://igormcoelho.github.io), bem como suas respectivas aplicações em períodos recentes.

![last-commit](https://img.shields.io/github/last-commit/igormcoelho/curso-estruturas-de-dados-i)

Lista completa de cursos: [igormcoelho/cursos](https://github.com/igormcoelho/cursos/)

Lista completa de módulos no repositório (sequência de estudos *sugerida*):

- Revisão/Tipos
- Análise de Complexidade (ainda a finalizar!)
- Pilhas
- Filas
- Conjuntos Simples (útil para revisar algoritmos clássicos de ordenação!)
- Sacos e Listas
- Árvores
- Árvores de Busca
- Dicionários e Tabelas de Dispersão
- Dicionários Ordenados e Árvores Auto-balanceadas (AVL e Rubro-Negra)
- Filas de Prioridade
- Árvores B

O curso também inclui conceitos abstratos como:

- Vista e Vista Mutavel (o conceito de *lightweight view* de linguagens modernas)
- Iteradores (similares aos conceitos de Java, mas compatíveis com os de C++)
- Percorrivel (o conceito de *range* em C++, ou `Iterable` em Java, ou `iterable` em Python)

Tópicos mais avançados como Grafos em geral são explorados como trabalho no curso.


Materiais PDF-HTML:

1. Introdução
   - [Introdução NOVO](slides/1-intro-tipos/1-intro-tipos.md): [PDF](slides/1-intro-tipos/1-intro-tipos.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/1-intro-tipos/index.html)
   - [ENGLISH - Introduction - Translated](slides/1-en-intro-types/1-en-intro-types.md): [PDF](slides/1-en-intro-types/1-en-intro-types.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/1-en-intro-types/index.html)
   - [Revisão/Tipos ANTIGO](slides/1-revisao-tipos/1-revisao-tipos.md): [PDF](slides/1-revisao-tipos/1-revisao-tipos.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/1-revisao-tipos/index.html)
   - Vídeos YouTube: [Parte 1](https://youtu.be/byZLHu4kTb0) [Parte 2](https://youtu.be/2Bo7MYFCJ0o)
   - Observação: a Parte 2 contém algumas falhas no áudio, que pretendo corrigir no futuro. Como é uma etapa extra (prática), não compromete o conteúdo em si da aula.  
1. [Pilhas](slides/3-pilhas/3-pilhas.md): [PDF](slides/3-pilhas/3-pilhas.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/3-pilhas/index.html)
   - Exemplo de pilha na STL: [main_pilha.cpp](./material/3-pilhas/main_pilha.cpp)
   - Vídeos YouTube: [Pilhas e Implementações](https://youtu.be/2J1EdzSZ1NQ) - Análise de Complexidade *(nas próximas semanas)*
   - Novos conceitos:
      * `PilhaTAD<T>`: `empilha(t)`, `desempilha()`, `topo()`, `tamanho()`
1. [Filas](slides/4-filas/4-filas.md): [PDF](slides/4-filas/4-filas.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/4-filas/index.html)
   - Exemplo de fila na STL: [main_fila.cpp](./material/4-filas/main_fila.cpp)
   - Vídeos YouTube: [Filas e Implementações](https://youtu.be/pZ36rzfSxYs) - Análise de Complexidade *(nas próximas semanas)*
   - Novos conceitos:
      * `FilaTAD<T>`: `enfileira(t)`, `desenfileira()`, `frente()`, `tamanho()`
1. Revisão/Treino TAD Sequencial: [Conjunto Simples](slides/2-conjunto-simples/2-conjunto-simples.md): [PDF](slides/2-conjunto-simples/2-conjunto-simples.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/2-conjunto-simples/index.html)
   - Novos conceitos:
      * `ConjuntoSimplesTAD<T>`: `pertence(x)`, `insere(x)`, `remove(x)`, `tamanho()`
1. [Sacos e Listas](slides/2-sacos/2-sacos.md): [PDF](slides/2-sacos/2-sacos.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/2-sacos/index.html)
   - Exemplo de implementação: [main.cpp](./slides/2-sacos/impl/main.cpp) [ListaEncadeada.hpp](./slides/2-sacos/impl/ListaEncadeada.hpp) [SacoTAD.hpp](./slides/2-sacos/impl/SacoTAD.hpp) [SacoVetor.hpp](./slides/2-sacos/impl/SacoVetor.hpp) [makefile (GNU c++17)](./slides/2-sacos/impl/makefile)
   - Novos conceitos: 
      * `VistaTAD`: `le()`  (com tipo associado `Tipo`)
      * `VistaMutavelTAD`: `le()`, `altera(t)`
      * `IteradorTAD<T>`: `le()`, `proximo()`, `terminou()` (satisfaz `VistaTAD`)
      * `PercorrivelTAD<T>`: `iterador()`
      * `SacoTAD<T>`: `adiciona(t)`, `busca(t)`, `remove(it)`, `tamanho()`
   - Tópico Avançado: [Sacos Ordenados](slides/2-sacos-ordenados/2-sacos-ordenados.md): [PDF](slides/2-sacos-ordenados/2-sacos-ordenados.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/2-sacos-ordenados/index.html)
   - Novos conceitos: 
      * `SacoOrdenadoTAD<T>`: `buscaMaiorIgual(t)`, `buscaMaior(t)` (satisfaz `SacoTAD<T>`)
1. Árvores e Árvores de Busca
   - [Árvores](slides/5-arvores/5-arvores.md): [PDF](slides/5-arvores/5-arvores.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/5-arvores/index.html)
   - [Árvores de Busca](slides/5-arvores-busca/5-arvores-busca.md): [PDF](slides/5-arvores-busca/5-arvores-busca.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/5-arvores-busca/index.html)
   - Vídeos YouTube: [Árvores Parte 1/2](https://youtu.be/Yd6Wda879Q4) 
1. Dicionários: 
   - [Dicionários e Tabelas de Dispersão](slides/6-dicionarios-hash/6-dicionarios-hash.md): [PDF](slides/6-dicionarios-hash/6-dicionarios-hash.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/6-dicionarios-hash/index.html)
      * Conceito `DicionarioTAD<K, V>`: `tem(c)`, `consulta(c)`, `adiciona(c, v)`, `remove(c)`, `tamanho()`
   - [Dicionários Ordenados e Árvores Balanceadas](slides/6-dicionarios/6-dicionarios.md): [PDF](slides/6-dicionarios/6-dicionarios.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/6-dicionarios/index.html)
      * Tipos `Vista<T>` e `VistaMutavel<T>` (versões genéricas das vistas)
      * Tipo `Entrada<K, V>`: `chave` (`Vista<K>`) e `valor` (`VistaMutavel<V>`)
      * Conceito `DicionarioOrdenadoTAD<K, V>`: `buscaMaiorIgual(c)`, `buscaMaior(c)` (satisfaz `DicionarioTAD<K, V>` e `PercorrivelTAD<Entrada<K, V>>`)
   - Vídeos YouTube: [Dicionários e Árvores de Busca Parte 1/2](https://youtu.be/Y_jx6sMQyf8) 
   - Material Fábio Protti: [Arvores de Busca 1](http://www.ic.uff.br/~fabio/Aula-arvores-binarias-de-busca-1.pdf)
   - Material Fábio Protti: [Arvores de Busca 2](http://www.ic.uff.br/~fabio/Aula-arvores-binarias-de-busca-2.pdf)
1. [Filas de Prioridade](slides/7-filas-prioridade/7-filas-prioridade.md): [PDF](slides/7-filas-prioridade/7-filas-prioridade.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/7-filas-prioridade/index.html)
   - Novos conceitos:
      * `FilaPrioridadeTAD<T>`: `frente()`, `insere(t)`, `remove()`, `tamanho()`
   - Vídeos YouTube (2020): [Filas de Prioridade Parte 1/2](https://youtu.be/SA-RgtmLWkM) 
   - Vídeos YouTube (2021):  [Filas de Prioridade Parte 2/2](https://youtu.be/q0kRz4oz_7A)


***Observação:*** **alguns módulos só são oferecidos para cursos específicos.*

-------

## Cursos recentes

- Algoritmos - PPG-CComp-UERJ
   * [Pós-Graduação 2021.1 PPG-CComp](./uerj-ccomp-alg-2021-1) (jun./2021-...)
   * Instituto de Matemática e Estatística (IME) - Universidade do Estado do Rio de Janeiro (UERJ)
- Estruturas de Dados para Sistemas de Informação - TCC00331
   * [Graduação 2021.1](./uff-edsi-2021-1) (jun./2021-set./2021)
   * Instituto de Computação (IC) - Universidade Federal Fluminense (UFF)

- Estrutura de Dados e Algoritmos (PGC EDA)
   * [Pós-Graduação 2021.1](./uff-pgc-eda-2021-1) (mar./2021-jun./2021)
   * Instituto de Computação (IC) - Universidade Federal Fluminense (UFF)

- Estruturas de Dados para Sistemas de Informação - TCC00331
   * [Graduação 2020.2](./uff-edsi-2020-2) (fev./2021-mai./2021)
   * Instituto de Computação (IC) - Universidade Federal Fluminense (UFF)

- Estruturas de Dados para Sistemas de Informação - TCC00331
   * [Graduação 2020.1](./uff-edsi-2020-1) (set./2020-dez./2020)
   * Instituto de Computação (IC) - Universidade Federal Fluminense (UFF)

-------

## Sobre gravações

Gravações disponibilizadas no YouTube e Classroom foram feitas com OBS (obrigado pelas dicas Mateus Nazário). Algumas dicas:

- https://medium.com/@igormcoelho/dicas-para-obs-no-linux-para-google-meet-8ac102972183

Utilizei o Okular para marcação do PDF (obrigado Matheus Nohra Haddad pelas dicas).

## Como esses slides foram feitos?

Estes slides foram feitos em `markdown` e `pandoc` (super fácil!) de acordo com o tutorial [ilectures-pandoc](https://github.com/igormcoelho/ilectures-pandoc).

Basicamente, é necessário instalar o pandoc e, opcionalmente, copiar alguns filtros úteis do tutorial (dois arquivos python). Então, é possível gerar, a partir do `markdown`, uma versão PDF LaTeX+Beamer, e outra web utilizando RevealJS. O tutorial explica tudo em detalhes.

O mais legal é que a edição do slide tem uma visualização em tempo real, com plugins disponíveis para editores populares como Atom e VSCode.
Uma demonstração foi colocada no site do ilectures: [https://github.com/igormcoelho/ilectures-pandoc#demonstrations](https://github.com/igormcoelho/ilectures-pandoc#demonstrations).


### Deps

Pandoc + LaTeX

`python3 -m pip install pandoc-source-exec`
`python3 -m pip install pandoc-latex-color`

[pandoc 2.10.1](https://github.com/jgm/pandoc/releases/tag/2.10.1)



### Licença CC-BY 4.0

Você pode: (Share) copiar e redistribuir esse material em qualquer formato; (Adapt) adaptar esse material, mesmo que para uso comercial.

Você deve: (Attribution) dar crédito apropriado, bem como um link para o original e a indicação das mudanças que você fez.

Veja licença original [CreativeCommons CC-BY 4.0](https://creativecommons.org/licenses/by/4.0/)

```
curso-estruturas-de-dados-i (c) by Igor M. Coelho

curso-estruturas-de-dados-i is licensed under a
Creative Commons Attribution 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by/4.0/>.
```


Copyleft 2020
