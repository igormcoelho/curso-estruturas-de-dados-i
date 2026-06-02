import std;
using namespace std;
import saco_tad;
import saco_lista_encadeada;
import saco_vetor;

int
main()
{
  // SacoTAD auto l = ListaEnc1{}; // alguma implementação
  ListaEnc1 l;
  l.cria();
  l.adiciona('c');
  l.adiciona('a');
  l.adiciona('b');
  l.adiciona('a');
  print("{}\n", l.busca('a').terminou());             // 0
  print("{}\n", l.busca('d').terminou());             // 1
  print("{}\n", buscarec(l.itera(), 'd').terminou()); // 1
  print("N={}\n", l.N);                               // N=4
  for (auto it = l.itera(); !it.terminou(); it.proximo())
    print("{}\n", it.atual()); // a b a c
  //
  l.remove(l.busca('b'));
  print("N={}\n", l.N); // N=3
  for (auto x : l)
    print("{}\n", x); // a a c

  l.libera();
  print("N={}\n", l.N); // N=0

  // ==========================================================================

  print("    ====VETOR====    \n");

  // SacoTAD auto v = SacoVetor1{}; // alguma implementação
  SacoVetor1 v;
  v.cria();
  v.adiciona('c');
  v.adiciona('a');
  v.adiciona('b');
  v.adiciona('a');
  print("{}\n", v.busca('a').terminou()); // 0
  print("{}\n", v.busca('d').terminou()); // 1
  print("N={}\n", v.N);                   // N=4
  for (auto it = v.itera(); !it.terminou(); it.proximo())
    print("{}\n", it.atual()); // c a b a
  //
  v.remove(v.busca('b'));
  print("N={}\n", v.N); // N=3
  for (auto x : v)
    print("{}\n", x); // c a a

  v.libera();
  print("N={}\n", v.N); // N=0

  return 0;
}
