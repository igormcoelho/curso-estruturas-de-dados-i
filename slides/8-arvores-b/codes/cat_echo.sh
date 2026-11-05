#!/bin/bash
#echo "Arguments: $#"
if (( $# != 1 )); then
    # not a file, just use 'echo'
    echo "$@"
else
  # SINGLE argument: it may be a file (or not)
  #echo "It may be file: $1"
  if [ ! -f "$1" ]; then
    echo "$@"  # just 'echo'
  else
    cat "$1"
  fi
fi
