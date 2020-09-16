#include "IgorMachadoCoelho.hpp" // implementações do professor.. faça seu próprio arquivo .hpp!

#define CATCH_CONFIG_MAIN // catch2 main()
#include "catch.hpp"

// =======================
// testes para exercício 0
// -----------------------

TEST_CASE("ex0 - caso 0")
{
  REQUIRE(exercicio0("") == 0);
}

// =======================
// testes para exercício 1
// -----------------------

TEST_CASE("ex1 a=1 b=3")
{
  REQUIRE(exercicio1("1 3") == 6);
}

TEST_CASE("ex1 a=1 b=10")
{
  REQUIRE(exercicio1("1 10") == 55);
}

// ===================
// testes para exemplo
// -------------------

TEST_CASE("exemplo n=3 3 2 5")
{
  // 3 + 2 + 5 = 10
  REQUIRE(exemplo("\t3     3    2 \n\t 5") == 10);
}

// testado com Catch v2.13.1
// mais testes virão aqui no futuro...


