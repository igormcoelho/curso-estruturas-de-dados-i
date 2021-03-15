## Estruturas de Dados I

Materiais gerais de Estruturas de Dados I, bem como suas respectivas aplicações em períodos recentes.

Lista completa de módulos no repositório:

- Revisão/Tipos
- Análise de Complexidade
- Listas
- Pilhas
- Filas
- Árvores
- Árvores de Busca e Mapas
- Filas de Prioridade
- Grafos

Materiais PDF-HTML:

1. [Revisão/Tipos](slides/1-revisao-tipos/1-revisao-tipos.md): [PDF](slides/1-revisao-tipos/1-revisao-tipos.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/1-revisao-tipos/index.html)
   - Vídeos YouTube: [Parte 1](https://youtu.be/byZLHu4kTb0) [Parte 2](https://youtu.be/2Bo7MYFCJ0o)
   - Observação: a Parte 2 contém algumas falhas no áudio, que pretendo corrigir no futuro. Como é uma etapa extra (prática), não compromete o conteúdo em si da aula.
1. [Pilhas](slides/3-pilhas/3-pilhas.md): [PDF](slides/3-pilhas/3-pilhas.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/3-pilhas/index.html)
   - Exemplo de pilha na STL: [main_pilha.cpp](./material/3-pilhas/main_pilha.cpp)
   - Vídeos YouTube: [Pilhas e Implementações](https://youtu.be/2J1EdzSZ1NQ) - Análise de Complexidade *(nas próximas semanas)*
1. [Filas](slides/4-filas/4-filas.md): [PDF](slides/4-filas/4-filas.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/4-filas/index.html)
   - Exemplo de fila na STL: [main_fila.cpp](./material/4-filas/main_fila.cpp)
   - Vídeos YouTube: [Filas e Implementações](https://youtu.be/pZ36rzfSxYs) - Análise de Complexidade *(nas próximas semanas)*
1. [Árvores](slides/5-arvores/5-arvores.md): [PDF](slides/5-arvores/5-arvores.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/5-arvores/index.html)
   - Vídeos YouTube: [Árvores Parte 1/2](https://youtu.be/Yd6Wda879Q4) 
1. [Dicionários e Árvores de Busca](slides/6-dicionarios/6-dicionarios.md): [PDF](slides/6-dicionarios/6-dicionarios.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/6-dicionarios/index.html)
   - Vídeos YouTube: [Dicionários e Árvores de Busca Parte 1/2](https://youtu.be/Y_jx6sMQyf8) 
   - Material Fábio Protti: [Arvores de Busca 1](http://www.ic.uff.br/~fabio/Aula-arvores-binarias-de-busca-1.pdf)
   - Material Fábio Protti: [Arvores de Busca 2](http://www.ic.uff.br/~fabio/Aula-arvores-binarias-de-busca-2.pdf)
1. [Filas de Prioridade](slides/7-filas-prioridade/7-filas-prioridade.md): [PDF](slides/7-filas-prioridade/7-filas-prioridade.pdf) [Online](https://igormcoelho.github.io/curso-estruturas-de-dados-i/slides/7-filas-prioridade/index.html)
   - Vídeos YouTube: [Filas de Prioridade Parte 1/2](https://youtu.be/SA-RgtmLWkM) 


***Observação:*** **alguns módulos só são oferecidos para cursos específicos.*

-------

## Cursos recentes

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
