all: app_avl 

app_avl:
	g++-16 -g -std=c++26 -fcontracts -fmodules -fmodule-only --compile-std-module
	g++-16 -g -std=c++26 -fcontracts -fmodules --compile-std-module ../arvores.cppm ../avl.cppm main_avl.cpp -o app_avl

.PHONY: app_avl

