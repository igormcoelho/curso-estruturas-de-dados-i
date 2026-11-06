## Estruturas de Dados I

Materiais gerais de Estruturas de Dados I do [Prof. Igor Machado Coelho](https://igormcoelho.github.io), bem como suas respectivas aplicações em períodos recentes.

![last-commit](https://img.shields.io/github/last-commit/igormcoelho/curso-estruturas-de-dados-i)

Lista completa de cursos: [igormcoelho/cursos](https://github.com/igormcoelho/cursos/)

Lista completa de módulos no repositório (sequência de estudos *sugerida*):

1. Introdução a Tipos e Análise de Complexidade
2. Pilhas
3. Filas
4. Coleções Lineares e Iteração
   - Conjuntos Simples
   - Vistas, Iteradores e Percorríveis
   - Sacos e Listas
5. Árvores 
   - Conceitos de Árvores 
   - Árvores de Busca
6. Dicionários
   - Dicionários com Tabelas de Dispersão
   - Dicionários Ordenados e Árvores Auto-balanceadas (AVL e Rubro-Negra)
7. Filas de Prioridade
8. Árvores B e B+

**Cuidado com o Módulo 4:** *ele pode ser bastante avançado, dependendo da sua base prévia em programação estruturada: algoritmos clássicos de ordenação, listas encadeadas, vistas e iteradores.*

Tópicos mais avançados como Grafos em geral são explorados como trabalho no curso.

Materiais PDF-HTML:

1. Introdução (Tipos e Análise de Complexidade)
   - [Introdução: Tipos e Análise de Complexidade](slides/1-intro-tipos/1-intro-tipos.md): [PDF](slides/1-intro-tipos/1-intro-tipos.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/1-intro-tipos/index.html)
   - [ENGLISH - Introduction - Translated](slides/1-en-intro-types/1-en-intro-types.md): [PDF](slides/1-en-intro-types/1-en-intro-types.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/1-en-intro-types/index.html)
   - [Revisão/Tipos ANTIGO](slides/1-revisao-tipos/1-revisao-tipos.md): [PDF](slides/1-revisao-tipos/1-revisao-tipos.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/1-revisao-tipos/index.html)
   - Vídeos YouTube: [Parte 1](https://youtu.be/byZLHu4kTb0) [Parte 2](https://youtu.be/2Bo7MYFCJ0o)
   - Observação: a Parte 2 contém algumas falhas no áudio, que pretendo corrigir no futuro. Como é uma etapa extra (prática), não compromete o conteúdo em si da aula.  
   - Novos tipos:
      * `SpanInt`: `tamanho()`, `le(i)`, `altera(i, v)`, `fatia(a, b)` (vista de um trecho de vetor, sem posse)
2. [Pilhas](slides/2-pilhas/2-pilhas.md): [PDF](slides/2-pilhas/2-pilhas.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/2-pilhas/index.html)
   - Exemplo de pilha na STL: [main_pilha.cpp](./material/2-pilhas/main_pilha.cpp)
   - Vídeos YouTube: [Pilhas e Implementações](https://youtu.be/2J1EdzSZ1NQ) - Análise de Complexidade *(nas próximas semanas)*
   - Novos conceitos:
      * `PilhaTAD<T>`: `empilha(t)`, `desempilha()`, `topo()`, `tamanho()`
3. [Filas](slides/3-filas/3-filas.md): [PDF](slides/3-filas/3-filas.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/3-filas/index.html)
   - Exemplo de fila na STL: [main_fila.cpp](./material/3-filas/main_fila.cpp)
   - Vídeos YouTube: [Filas e Implementações](https://youtu.be/pZ36rzfSxYs) - Análise de Complexidade *(nas próximas semanas)*
   - Novos conceitos:
      * `FilaTAD<T>`: `enfileira(t)`, `desenfileira()`, `frente()`, `tamanho()`
4. Coleções Lineares e Iteração: Conjuntos Simples, Vistas e Sacos
   - [Conjunto Simples](slides/4-conjunto-simples/4-conjunto-simples.md): [PDF](slides/4-conjunto-simples/4-conjunto-simples.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/4-conjunto-simples/index.html)
   - Novos conceitos:
      * `ConjuntoSimplesTAD<T>`: `pertence(x)`, `insere(x)`, `remove(x)`, `tamanho()`
   - [Vistas, Iteradores e Percorríveis](slides/4-vistas/4-vistas.md): [PDF](slides/4-vistas/4-vistas.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/4-vistas/index.html)
   - Novos conceitos:
      * `VistaTAD`: `le()`  (com tipo associado `Tipo`)
      * `VistaMutavelTAD`: `le()`, `altera(t)`
      * `VistaVetorTAD<T>`: `tamanho()`, `le(i)`
      * `VistaMutavelVetorTAD<T>`: `tamanho()`, `le(i)`, `altera(i, t)` (satisfaz `VistaVetorTAD<T>`; ex: `SpanInt`)
      * `IteradorTAD<T>`: `le()`, `proximo()`, `terminou()` (satisfaz `VistaTAD`)
      * `PercorrivelTAD<T>`: `iterador()`
   - [Sacos e Listas](slides/4-sacos/4-sacos.md): [PDF](slides/4-sacos/4-sacos.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/4-sacos/index.html)
   - Exemplo de implementação: [main.cpp](./slides/4-sacos/impl/main.cpp) [ListaEncadeada.hpp](./slides/4-sacos/impl/ListaEncadeada.hpp) [SacoTAD.hpp](./slides/4-sacos/impl/SacoTAD.hpp) [SacoVetor.hpp](./slides/4-sacos/impl/SacoVetor.hpp) [makefile (GNU c++17)](./slides/4-sacos/impl/makefile)
   - Novos conceitos: 
      * `SacoTAD<T>`: `adiciona(t)`, `busca(t)`, `remove(it)`, `tamanho()`
   - Tópico Avançado: [Sacos Ordenados](slides/4-sacos-ordenados/4-sacos-ordenados.md): [PDF](slides/4-sacos-ordenados/4-sacos-ordenados.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/4-sacos-ordenados/index.html)
   - Novos conceitos: 
      * `SacoOrdenadoTAD<T>`: `buscaMaiorIgual(t)`, `buscaMaior(t)` (satisfaz `SacoTAD<T>`)
5. Árvores e Árvores de Busca
   - [Árvores](slides/5-arvores/5-arvores.md): [PDF](slides/5-arvores/5-arvores.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/5-arvores/index.html)
   - [Árvores de Busca](slides/5-arvores-busca/5-arvores-busca.md): [PDF](slides/5-arvores-busca/5-arvores-busca.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/5-arvores-busca/index.html)
   - Vídeos YouTube: [Árvores Parte 1/2](https://youtu.be/Yd6Wda879Q4) 
6. Dicionários: 
   - [Dicionários e Tabelas de Dispersão](slides/6-dicionarios-hash/6-dicionarios-hash.md): [PDF](slides/6-dicionarios-hash/6-dicionarios-hash.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/6-dicionarios-hash/index.html)
      * Conceito `DicionarioTAD<K, V>`: `tem(c)`, `consulta(c)`, `adiciona(c, v)`, `remove(c)`, `tamanho()`
   - [Dicionários Ordenados e Árvores Balanceadas](slides/6-dicionarios/6-dicionarios.md): [PDF](slides/6-dicionarios/6-dicionarios.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/6-dicionarios/index.html)
      * Tipos `Vista<T>` e `VistaMutavel<T>` (versões genéricas das vistas)
      * Tipo `Entrada<K, V>`: `chave` (`Vista<K>`) e `valor` (`VistaMutavel<V>`)
      * Conceito `DicionarioOrdenadoTAD<K, V>`: `buscaMaiorIgual(c)`, `buscaMaior(c)` (satisfaz `DicionarioTAD<K, V>` e `PercorrivelTAD<Entrada<K, V>>`)
   - Vídeos YouTube: [Dicionários e Árvores de Busca Parte 1/2](https://youtu.be/Y_jx6sMQyf8) 
   - Material Fábio Protti: [Arvores de Busca 1](http://www.ic.uff.br/~fabio/Aula-arvores-binarias-de-busca-1.pdf)
   - Material Fábio Protti: [Arvores de Busca 2](http://www.ic.uff.br/~fabio/Aula-arvores-binarias-de-busca-2.pdf)
7. [Filas de Prioridade e Heaps](slides/7-filas-prioridade/7-filas-prioridade.md): [PDF](slides/7-filas-prioridade/7-filas-prioridade.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/7-filas-prioridade/index.html)
   - Novos conceitos:
      * `FilaPrioridadeTAD<T>`: `frente()`, `insere(t)`, `remove()`, `tamanho()`
   - Vídeos YouTube (2020): [Filas de Prioridade Parte 1/2](https://youtu.be/SA-RgtmLWkM) 
   - Vídeos YouTube (2021):  [Filas de Prioridade Parte 2/2](https://youtu.be/q0kRz4oz_7A)
8. [Árvores B e B+](slides/8-arvores-b/8-arvores-b.md): [PDF](slides/8-arvores-b/8-arvores-b.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/8-arvores-b/index.html)

***Observação:*** *alguns módulos só são oferecidos para cursos específicos.*

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
