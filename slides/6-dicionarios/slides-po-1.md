---
author: Igor M. Coelho
title: Demonstration Beamer/Reveal
date: April 8, 2020
transition: cube
fontsize: 10
header-includes:
- <link rel="stylesheet" type="text/css" href="general.css">
- <link rel="stylesheet" type="text/css" href="reveal-beamer.css">
---


# Part 1: Basics

-------

## Basic Formatting

Text <span latex-color="blue" style="color:blue">formatting</span> requires a few things, such as lists (prefix `-`, `*` or `+`):

- **bold** (Markdown `**bold**`, LaTeX `\textbf{bold}`)
- *italics* (Markdown `*italics*`, LaTeX `\textit{italics}`)
  + ***bold and italics*** (Markdown `***` symbol, LaTeX `\textbf{\textit{...}}`)

Enumeration lists can use `1.` or `#.` prefix:

1. one
1. two

::: {.block}

### An important reminder for $\text{\LaTeX}$ {#reminder}
Use  <span latex-color="red" style="color: red;">math mode</span> as `$\sum_{i=0}^{n}\sqrt{i}$` for $\sum_{i=0}^{n}\sqrt{i}$.

:::

For color use "`--filter pandoc-latex-color`": then use `<span latex-color="green" style="color:green;">abc</span>`.

----------

## Headers and Tables {#header-tables}

Headers can become different things (e.g,`--slide-level 2` on Pandoc):

| Slide   | Header 1 (`#`) | Header 2 (`##`) | Header 3 (`###`) |
| :------ | :------------  | :--------------: | ---------------: |
| Level 1 |     Frame      |           Box                     ||
| Level 2 |  Section <br> Section  |           Frame |              Box |
| Level 3 |    Section     |      Subsection |            Frame |

You just need to use standard markdown table notation:

\footnotesize

```
| Slide   | Header 1 (`#`) | Header 2 (`##`) | Header 3 (`###`) |
| :---    |    :----       |         :---:   |          ---:    |
| Level 1 | Frame          | Box                               ||
| Level 2 | Section        | Frame           | Box              |
| Level 3 | Section        | Subsection      | Frame            |
```

-------

## Images {#sec-images1}

We saw [basic formatting](#basic-formatting).
To insert figures, use Markdown notation:
`![AltText](./filename.jpg "Title")`

To resize it and visualize on Atom, Beamer and Reveal, just use Pandoc `bracketed_spans` notation: `{width=80%}`.

![An universe picture](./universe.jpg "An example image"){width=30%}

Example:
`![An universe picture](./universe.jpg "An example image"){width=40%}`

-------


## Organization and Columns (Part I)

Let's divide in three parts (35%, 30%, 35%):

<!-- <div class="columns">
<div class="column" width="35%" style="max-width:35%;"> -->

::::::::::::: {.columns}

::::: {.column width=35%}

- First column
  - Some item

:::::

<!--
</div>
<div class="column" width="30%" style="max-width:30%;">  -->

::::: {.column width=30%}

**Just an equation:** $$\sum_{i=0}^{n}\sqrt{i}$$
<!--
</div>
<div class="column" width="35%" style="max-width:35%;"> -->

:::::

::::: {.column width=35%}

1. A third column
   * Something
1. One extra item
<!--
</div>
</div> -->

:::::

:::::::::::::

*To create multiple columns in a compatible way, we can use:*
\footnotesize

```html
<div class="columns">
  <div class="column" width="35%" style="max-width:35%;">
     Content for column with 35% size
  </div>
</div>
```

-------

## Fenced Divs {#fenceddivs .allowframebreaks}

<!-- not working on typora nor Atom yet -->

This code should allow organizing text into column.

::::::::::::: {.columns}

::::: {.column width=100%}

::: {.centered}

\centering

*Single centered column*

:::

:::::

:::::::::::::

```
::::::::::::: {.columns}
::::: {.column width=100%}
::: {.centered}
\centering
*Single centered column*
:::
:::::
:::::::::::::
```

This doesn't work on Typora or Atom, but works on LaTeX and Reveal.

For centering, just `::: {.centered}` and `\centering` would be enough.

---------


## Organization and Columns (Part II)  

Double column with image on side (20% and 80%):

<div class="columns">
<div class="column" width="50%" style="max-width:50%;">

- One topic
  - Another item
- Second topic
  - One extra
    - One deeper level

</div>
<div class="column" width="50%" style="max-width:50%;">

<style> img[alt="An universe picture"] { width: 70%; } </style>
![An universe picture](./universe.jpg "An example image"){width=70%}

</div>
</div>

### Fenced Divs
Note that Pandoc 2.9 provides a special syntax for fenced divs, like: `::::::: {.columns}` and  `::: {.column width="50%"}`. This is not recommended because Atom Preview will not understand it. For the same reason, use both `max-width=50%;` and `width="50%"`.

<br/><br/><br/><br/>

-------

## Some notes

<div class="notes right">
These notes are not on main slide.

- You can use `<div class="notes">`
- Or right-align: `<div class="notes right">`
</div>

This slide will only ask you to press `s` on Reveal.
This will put you on `Speaker Mode` and you'll see the notes.

### For Beamer
This is more complicated, but possible.
It requires an specialized `pdf` player for multiple monitors, like `pdfpc` or `pympress`.

```
%\documentclass[notes]{beamer}       % frame + notes
\documentclass[notes=only]{beamer}   % only notes
%\documentclass{beamer}              % only frames
```

# Thanks

-----

## Last advices {#hh-lastadvices}

Never add frame breaks `------` before Level 1 headers (`#`). Otherwise it will create a blank slide ;)


#### Practice on Atom, VSCode or Typora editors

On Atom, install one of these plugins:

- Markdown Preview Plus: `https://atom.io/packages/markdown-preview-plus`
- Markdown Preview Enhanced: `https://atom.io/packages/markdown-preview-enhanced`

Comparison on syntax for Markdown-It and Pandoc:
see [Atom community discussion](https://github.com/atom-community/markdown-preview-plus/wiki/markdown-it-vs.-pandoc).

See more reveal.js themes on `https://github.com/hakimel/reveal.js`

::::::::::::: {.columns}

::::: {.column width=100%}

::: {.centered}

\centering

***See you next time!***

:::

:::::

:::::::::::::
