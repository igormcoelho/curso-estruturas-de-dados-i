---
author: Igor M. Coelho
title: Estruturas de Dados I
date: 30/08/2020
transition: linear
fontsize: 10
header-includes:
- <link rel="stylesheet" type="text/css" href="general.css">
- <link rel="stylesheet" type="text/css" href="reveal-beamer.css">
---





# Introdução ao Curso

------

## Boas vindas

Bem-vind@s ao curso de *Estruturas de Dados para Sistemas de Informação*

Curso:

- Estruturas de Dados para Sistemas de Informação - `TCC00331` - C.H. 64
- Site: https://igormcoelho.github.io/curso-estruturas-de-dados-i

Links úteis:

- http://www.ic.uff.br/index.php/pt/curriculo-e-disciplinas/disciplinas-obrigatorias
- https://app.uff.br/graduacao/quadrodehorarios
- https://app.uff.br/iduff
- Instituto de Computação (IC/UFF) - www.ic.uff.br
- Universidade Federal Fluminense (UFF) - www.uff.br

--------

## Sobre mim


::::::::::::: {.columns}

::::: {.column width=40%}

![Prof. Igor M. Coelho](./img/igor-lattes.jpeg "Prof. Igor Machado Coelho"){width=50%}

e-mail (com prefixo no assunto 'EDSI-2020.1'):

imcoelho at ic.uff.br (emergência)

:::::

::::: {.column width=60%}

Me chamo Igor, e é um prazer apresentar esse curso para vocês! Sou professor e pesquisador da UFF, desenvolvedor de algoritmos e sistemas (a maioria de código-aberto), bem como suas respectivas estruturas de dados (vocês saberão em breve o que é isso!). Podem me contactar pelos emails ao lado (*substituam o 'at' por '@'*), mas peço que priorizem o uso da ferramenta de Classroom do curso, que consigo responder mais rápido (com alcance aos demais alunos).
Esse curso está disponível no meu site pessoal no github: https://igormcoelho.github.io/curso-estruturas-de-dados-i


:::::


:::::::::::::

--------

## Sobre vocês

Gostaria que se apresentassem também (*nas aulas síncronas*) para nos conhecermos melhor! 

Ninguém aprende 100% do que o professor ensina, e nem o professor consegue ensinar 100% de um conteúdo, então cabe aos alunos: *ler*, *estudar* e *questionar* (muito!). **Juntos** podemos trabalhar para transmitir esse conhecimento valioso para cada um de vocês.

Sempre que tiverem uma dúvida ou curiosidade, perguntem! Toda pergunta é valiosa, e o conhecimento é construído em pequenas porções.

-------

## Acordo Aluno-Professor

*Para esse curso funcionar: tenham dedicação!*

É fundamental: 

- Não atrasar entrega de trabalho, mas caso precisem de uma extensão, solicitem antes do prazo! (*atrasos podem reduzir ou até zerar notas*)
- Buscar ao máximo não perder nenhuma aula (síncrona), e caso percam, busquem o quanto antes suprir esse conteúdo
- Nunca, em hipótese alguma, copiem um trabalho pronto! Além dos efeitos práticos (como perda de nota ou demais sanções previstas nas normas), não se enganem: quem mais perde é o aluno. Conhecimento é o bem mais valioso!
- **Sempre** citem as fontes, especialmente para trechos de textos. Sempre que possivel, indique a licença de uso de imagens e códigos (os buscadores permitem buscas com licença livre).


--------


## Período 2020.1 com aulas remotas

Atividades com aulas remotas em 2020.1

- Período: 14/09/2020 (segunda-feira) - 15/12/2020 (terça-feira)

- Lançamento de notas: 14/12/2020 (último encontro)

Teremos aulas síncronas em horários regulares e outras diversas atividades assíncronas complementares (vídeos, textos, trabalhos, ...) para suprir toda a carga horária.

Serão oferecidas aprox. 30% de aulas síncronas, além de atividades de apresentação/discussão síncronas.

Vide: *INSTRUÇÃO DE SERVIÇO PROGRAD Nº 15/2020, DE 25 DE AGOSTO DE 2020*


---------

## Horários Síncronos

Horários do curso: segunda e quarta 20h-22h.

Horários síncronos*: segundas 20h-22h (quartas sempre serão assíncronos)

(*) Algumas exceções estão previstas e algumas aulas poderão ser alteradas (caso seja necessário), mas esta é a regra geral.

---------

## Ementa

1. PILHAS
2. FILAS
3. FILAS COM PRIORIDADES
4. ÁRVORES (BINÁRIA, BINÁRIA DE BUSCA, BALANCEADAS)
5. GRAFOS
(REPRESENTAÇÃO, BUSCA LARGURA E PROFUNDIDADE, CAMINHOS)
6. TABELA DE DISPERSÃO

--------

## Avaliação

Haverá atividades avaliativas assícronas (A), como listas de exercícios e resumos de textos/vídeos (R). Haverá apenas uma VS com conteúdo escrito (VS). Além disso, haverá atividades com prova (V) e apresentação (P) (*com formação opcional de grupos por tema de interesse*).

A nota N do curso será:

A = (30%R + 70%V)/2

N1 = (A + P)/2

De acordo com as normas regulares da UFF, a nota mínima N1 para aprovação é 6.

Caso contrário, será necessário fazer a VS.

N2 = (N1 + VS)/2

--------

## Cronograma (I)

- Período: 14/09/2020 - 15/12/2020

Tipo = Sinc./Asinc.

| Data       | Atividade                       | Tipo    |
| :---       |   :----                         | :---    |
| 14/09/2020 |  Revisão & Tipos            |  Sinc.  | 
| 16/09/2020 |  Leitura & Debates              |  Asinc. |
| 21/09/2020 |  Pilhas & Filas                 |  Sinc.  |
| 23/09/2020 |  Leitura & Debates              |  Asinc. |
| 28/09/2020 |  Árvores  I                     |  Sinc.  |
| 30/09/2020 |  Leitura & Debates              |  Asinc. |
| 05/10/2020 |  Árvores II                     |  Sinc.  |
| 07/10/2020 |  Leitura & Debates              |  Asinc. |
| 12/10/2020 |  Filas de Prioridades           |  Sinc.  |
| 14/10/2020 |  Leitura & Debates              |  Asinc. |
| 19/10/2020 |  Revisão Geral                  |  Sinc.  |

------

## Cronograma (II)

| Data       | Atividade                       | Tipo    |
| :---       |   :----                         | :---    |
| 21/10/2020 |  Prova (V)                      |  *Asinc. |
| 26/10/2020 |  Grafos e Hash (conceitos)      |  Sinc.  |
| 28/10/2020 |  Leitura & Debates              |  Asinc. |
| 02/11/2020 |  Debates *                      |  *Asinc. |
| 04/11/2020 |  Debates *                      |  Asinc. |
| 09/11/2020 |  Apresentação (P)               |  Sinc.  |
| 11/11/2020 |  Debates (P)                    |  Asinc. |
| 16/11/2020 |  Apresentação (P)               |  Sinc.  |
| 18/11/2020 |  Debates (P)                    |  Asinc. |
| 23/11/2020 |  Apresentação (P)               |  Sinc.  |
| 24/11/2020 |  Debates (P)                    |  Asinc. |
| 30/11/2020 |  Apresentação (P)               |  Sinc.  |
| 02/12/2020 |  Debates (P)                    |  Asinc. |

-------

## Cronograma (III)

| Data       | Atividade                       | Tipo   |
| :---       |   :----                         | :---   |
| 07/12/2020 |  Segunda Chamada                |  *Asinc. |
| 09/12/2020 |  -                              |  Asinc. |
| 14/12/2020 |  VS                            |  *Asinc. |
| 15/12/2020 |  Lançamento Notas              |  *Asinc. |

-------

##  Apresentação (P)

O trabalho consiste em implementar e apresentar um tópico (subtópico da parte de grafos, hashes e outros tópicos classificados como "extra"). Deverá ser feito em formato artigo com no mínimo 3 membros (casos excepcionais serão analisados apenas caso não seja possível formar grupos).

A formação de grupos será pela plataforma, durante debates cada aluno irá indicar uma empresa de interesse (em um primeiro momento). Assim, serão agregados naturalmente grupos (por ordem cronológica de criação de grupos completos) com no máximo duas repetições por tema.

O formato de entrega será em artigo no padrão SBC (word ou LaTeX PDF) - máx 5 páginas - e apresentação síncrona.

Grupos deverão ser definidos no máximo até a data da prova (V). Haverá quatro dias possíveis para apresentação, mais um debate assíncrono das apresentações do dia.

**É necessário agendar previamente a apresentação! Façam o quanto antes!**

-------


## Linguagem Adotada

O conteúdo do curso será focado na análise de algoritmos, então
as técnicas apresentadas independem da linguagem de programação
adotada (valendo inclusive para pseudocódigo).

Porém, para fornecer um conteúdo dinâmico que pode ser testado e
experimentado pelos alunos em uma das linguagens mais utilizadas
atualmente no mundo, adotaremos as linguagens C/C++ (ambas
serão aceitas).

A linguagem C++ é uma extensão da linguagem C, adicionando
dois principais recursos interessantes: orientação a objetos e pro-
gramação genérica. *Não entraremos com profundidade em nenhum
destes dois assuntos, mas não se preocupe! Eles serão aprofunda-
dos em disciplinas futuras.* Somente recursos básicos das linguagens
C/C++ serão utilizados neste curso (e iremos revisá-los em breve!).


-------

## Bibliografia Recomendada

::::::::::::: {.columns}

::::: {.column width=40%}

![Livro Referência](./img/livro.jpg "Algoritmos Cormen"){width=50%}

:::::

::::: {.column width=60%}

Buscaremos suprir o conteúdo especialmente através de materiais com licença livre (slides, apostilas, vídeos, textos, ...). Como livro texto, recomendamos o livro: *"Algoritmos - Cormen, Rivest"*.
Veja Classroom para mais materiais.

:::::


::::::::::::: 


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

Exceto expressamente mencionado (e com as devidas ressalvas ao material cedido pelo prof. Fornazin), a licença será Creative Commons.

**Licença:** CC-BY 4.0 2020

Igor Machado Coelho