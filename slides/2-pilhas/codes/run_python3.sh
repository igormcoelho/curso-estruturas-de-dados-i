#!/bin/bash

#echo "Arguments: $# -> $@"

CMD=/usr/bin/python3

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
    echo "$@" | $CMD  # just 'echo' all
  elif [ -z "$1" ]; then
    #echo "EMPTY CODE! JUST RUN: $CMD ${@:2}"
    $CMD "${@:2}" # skip first empty argument
  else
    #echo "INVOKING $CMD ${@:1:$(($#-1))} FOR FILE: ${@: -1}"
    cat "${@: -1}"  | $CMD "${@:1:$(($#-1))}" # all but last
  fi
fi

#"${@:1:$(($#-1))}"
#`dirname $0`/cat_echo.sh "$@" | /usr/bin/python3
