all: app_arv

app_arv:
	g++-16 -std=c++26 -fcontracts -fmodules -fmodule-only --compile-std-module
	g++-16  -std=c++26 -fcontracts -fmodules --compile-std-module ../arvores.cppm main_arv.cpp -o app_arv
.PHONY: app_arv
