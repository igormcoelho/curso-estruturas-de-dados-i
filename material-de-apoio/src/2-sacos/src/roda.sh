#!/bin/sh
# uso: ./roda.sh clang++-23   (ou clang++-21, g++)
CXX=${1:-clang++}
FLAGS="-std=c++20 -fsyntax-only -Wno-unknown-warning-option \
 -Wdangling -Wdangling-gsl -Wreturn-stack-address \
 -Wlifetime-safety -Wlifetime-safety-permissive -Wlifetime-safety-invalidation"
for t in 1 2 3 4 5 6 7 8 9 10 11; do
  n=$($CXX $FLAGS -DT=$t main-lifetime-clang23.cpp 2>&1 | grep -cE 'warning|error')
  echo "T$t: $n aviso(s)/erro(s)"
  $CXX $FLAGS -DT=$t main-lifetime-clang23.cpp 2>&1 | grep -E 'warning|error' | sed 's/^/     /'
done

