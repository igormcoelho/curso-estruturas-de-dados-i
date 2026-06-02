#include <algorithm>
#include <cmath>
#include <iostream>

void
vprint(int v[], int N)
{
  for (unsigned i = 0; i < N; i++)
    printf("%d ", v[i]);
  printf("\n");
}

int troca_count = 0;

void
troca(int pos1, int pos2, int v[], bool count = true)
{
  int aux = v[pos1];
  v[pos1] = v[pos2];
  v[pos2] = aux;
  if (count)
    troca_count++;
}

// ================

int
pai(int pos)
{
  return (pos - 1) / 2;
}

int
filho1(int pos)
{
  return (2 * pos) + 1;
}

void
sobe(int pos, int v[], int N)
{
  int p = pai(pos);
  while (pos > 0) {
    // compara filho com pai (MAX)
    if (v[pos] <= v[p])
      break;
    // troca filho com pai
    troca(p, pos, v);
    // repete
    pos = p;
    p = pai(pos);
  }
}

void
desce(int pos, int v[], int N)
{
  int f = filho1(pos);
  while (f < N) {
    // prefere segundo filho ? (MAX)
    if ((f < N - 1) && (v[f + 1] > v[f]))
      f = f + 1;
    // compara filho com pai (MAX)
    if (v[f] <= v[pos])
      break;
    // troca filho com pai
    troca(f, pos, v);
    // repete
    pos = f;
    f = filho1(pos);
  }
}

void
constroi(int v[], int N)
{
  for (int i = N / 2 - 1; i >= 0; i--) {
    int t_bkp = troca_count;
    desce(i, v, N);
    std::cout << "constroi i=" << i << " trocas=" << (troca_count - t_bkp) << std::endl;
  }
}

void
constroi_sobe(int v[], int N)
{
  for (int i = 1; i < N; i++) {
    int t_bkp = troca_count;
    sobe(i, v, N);
    std::cout << "constroi_sobe i=" << i << " trocas=" << (troca_count - t_bkp) << std::endl;
  }
}

void
heapsort(int v[], int N, bool bdesce = true)
{
  // build heap
  if (bdesce)
    constroi(v, N);
  else
    constroi_sobe(v, N);
  std::cout << "TROCAS:" << troca_count << std::endl;
  //
  vprint(v, N);
  // sort
  for (unsigned i = 0; i < N; i++) {
    troca(0, N - i - 1, v, false);
    desce(0, v, N - i - 1);
  }
}

int
main()
{
  constexpr int N = ::pow(2, 5) - 1; //31; // 15
  std::cout << "N=" << N << std::endl;
  int v[N];
  for (unsigned i = 0; i < N; i++)
    v[i] = i;
  //std::random_shuffle(v, v + N);
  for (unsigned i = 0; i < N; i++)
    v[i] = i;

  //-----
  // 0 | 1 2 | 3 4 5 6 | 7 8 9 10 11 12 13 14 |
  //
  vprint(v, N);
  std::cout << "TROCAS:" << troca_count << std::endl;
  //
  heapsort(v, N);
  //
  vprint(v, N);
  std::cout << "TROCAS:" << troca_count << std::endl;
  //
  troca_count = 0;
  //
  for (unsigned i = 0; i < N; i++)
    v[i] = i;
  //
  vprint(v, N);
  std::cout << "TROCAS:" << troca_count << std::endl;
  //
  heapsort(v, N, false);
  //
  vprint(v, N);
  std::cout << "TROCAS:" << troca_count << std::endl;

  return 0;
}