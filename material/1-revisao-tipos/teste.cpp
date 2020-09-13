#include "resto.hpp"

#define CATCH_CONFIG_MAIN // catch2 main()
#include "catch.hpp"

TEST_CASE("Testa inicializacao do agregado Z") 
{
   auto z1 = Z{.x = 10};
   // verifica se, de fato, z1.x vale 10
   REQUIRE(z1.x == 10);
}

