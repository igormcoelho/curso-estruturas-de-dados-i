#!/bin/bash

# this compiles and executes c++ code
# TODO: we could maybe receive extra 'args' and add them as compile options.

#echo "Arguments: $# -> $@"

CXX=/usr/bin/g++
TMPCPP=/tmp/_test_pandoc.cpp
TMPAPP=/tmp/_app_test_pandoc
CMD="$CXX $TMPCPP -o $TMPAPP"

if [ $# -eq 0 ]; then
   echo "" # nothing to do
else
  #echo "ARG0: $0"
  #echo "ARG1: $1"
  #if [ -z "$1" ]; then echo "EMPTY"
  #fi
  #echo "ARG2: $2"
  # check if last argument is file
  if [ ! -f "${@: -1}" ]; then
    #echo "INVOKING $CMD FOR CODE: $@"
    #echo "$@" > $TMPCPP
    #cat  $TMPCPP
    $CMD && $TMPAPP
    #echo "$@" | $CMD  # just 'echo' all
  elif [ -z "$1" ]; then
    #echo "EMPTY CODE! JUST RUN: $CMD ${@:2}"
    cp "${@:2}" $TMPCPP
    #cat  $TMPCPP
    $CMD && $TMPAPP
  else
    #echo "INVOKING $CMD ${@:1:$(($#-1))} FOR FILE: ${@: -1}"
    #echo "REALFILE = ${@:1:$(($#-1))}"
    cp ${@:1:$(($#-1))} $TMPCPP
    #cat  $TMPCPP
    #echo "RUN $CMD"
    $CMD && $TMPAPP
  fi
fi

#"${@:1:$(($#-1))}"
#`dirname $0`/cat_echo.sh "$@" | /usr/bin/python3
