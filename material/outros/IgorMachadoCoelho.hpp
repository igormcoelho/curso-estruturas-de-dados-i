#ifndef EXERCICIOS_IGOR_HPP
#define EXERCICIOS_IGOR_HPP

#include<iostream>

// resolução exercício 0 (verifique se está correto)
int exercicio0(const char* cstr)
{
  return 1;
}

// resolução exercício 1 (verifique se está correto)
int exercicio1(const char* cstr)
{
  int a,b;
  sscanf(cstr, "%d %d",&a, &b);
  int s = 0;
  for(int i=a; i<=b; i++)
    s+=i;
  return s;
}

// exemplo útil: 
// ler N numeros e retornar a soma desses números
int exemplo(const char* cstr)
{
  int n, count;
  sscanf(cstr, "%d%n", &n, &count); cstr += count;
  //std::cout << "count=" << count << std::endl;
  int s = 0;
  while(n--)
  {
     int v = 0;
     sscanf(cstr, "%d%n", &v, &count); cstr += count;
     s += v;
     //std::cout << "v=" << v << std::endl;
  }
  return s;
}

// ============
// falta fazer:

int exercicio2(const char* cstr);

// dica: retorna uma tupla com 4 elementos (veja slides com std::make_tuple)
auto exercicio3(const char* cstr);

int exercicio4(const char* cstr);

int exercicio5(const char* cstr);

int exercicio6(const char* cstr);

// dica: retorno de 'char', não 'int'
char exercicio7(const char* cstr);

// dica: retorna uma tupla com 2 elementos (veja slides com std::make_tuple)
auto exercicio8(const char* cstr);

// dica: retorno de 'float', não 'int'
float exercicio9(const char* cstr);


#endif // EXERCICIOS_IGOR_HPP
