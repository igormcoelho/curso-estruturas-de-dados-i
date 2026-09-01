all: app_abb #app_avl 

gcc_bug:
	g++-16  -std=c++26 -fcontracts gcc_bug.cpp -freport-bug -o app_bug

app_avl:
	g++-16  -std=c++23 -fmodules -fsearch-include-path bits/std.cc avl.cpp -o app_avl
.PHONY: app_avl

app_abb:
	g++-16 -g -std=c++26 -fcontracts -fmodules -fmodule-only --compile-std-module
	g++-16 -g -std=c++26 -fcontracts -fmodules --compile-std-module ../arvores.cppm ../abb.cppm main_abb.cpp -o app_abb
# g++-16  -std=c++23 -fmodules -fsearch-include-path bits/std.cc main_abb.cpp -o app_abb
# 	g++-16 -std=c++26 -fcontracts -fmodules -fmodule-only --compile-std-module
#	g++-16 -std=c++26 -fcontracts -fmodules -fmodule-only arvores.cppm
.PHONY: app_abb

app_avl_26:
	g++-16  -std=c++26 -fcontracts -fmodules --compile-std-module avl.cpp -o app_avl_26
