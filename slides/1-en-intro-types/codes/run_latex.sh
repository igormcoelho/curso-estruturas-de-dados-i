#!/bin/bash

#echo "Arguments: $# -> $@"

# this script will get latex code and crop image

CMD=pdflatex

# TODO: verify if 'pdf2svg' and 'pdflatex' exists!

if [ $# -eq 0 ]; then
   echo "" # nothing to do
else
  #echo "=> $@"
  #echo "=> ${@: -1}"
  last="${@: -1}"          # only last
  baselast=$(basename "$last")
  rest="${@:1:$(($#-1))}"  # all but last
  if [ "${last: -4}" == ".tex" ]; then
    echo "INVOKING $CMD FOR .tex CODE: '$@'"
    echo "$@" | $CMD  # just 'echo' all
  elif [ -z "$1" ]; then
    #echo "EMPTY CODE! JUST RUN: $CMD ${@:2}"
    $CMD "${@:2}" # skip first empty argument
  elif [ "${last: -4}" == ".svg" ]; then
    #echo "REAL EXECUTION! $rest"
    (cd $(dirname "${last}") && echo "$rest" > "$baselast.tex" && $CMD "$baselast.tex"  2>/dev/null 1>&2)
    pdf2svg "$last.pdf" "$last" 2>/dev/null 1>&2
  else
    # FILE IS ON LAST POSITION!! WILL CAT IT!
    #echo "INVOKING $CMD ${@:1:$(($#-1))} FOR FILE: ${@: -1}"
    cat "${@: -1}"  | $CMD "${@:1:$(($#-1))}" # all but last
  fi
fi

#"${@:1:$(($#-1))}"
#`dirname $0`/cat_echo.sh "$@" | /usr/bin/python3
