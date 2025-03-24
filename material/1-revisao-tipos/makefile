CXX_GCC=g++-15
CXX_CLANG=clang++
CXXFLAGS_GCC   += -std=c++23  -fmodules -U_FORTIFY_SOURCE -fstack-protector -Wall  -Wunused-but-set-parameter -Wno-free-nonheap-object  -fno-omit-frame-pointer '-std=c++23' -fPIC
CXXFLAGS_CLANG += -std=c++23 -stdlib=libc++ -U_FORTIFY_SOURCE -fstack-protector -Wall -Wthread-safety -Wself-assign -Wunused-but-set-parameter -Wno-free-nonheap-object -fcolor-diagnostics -fno-omit-frame-pointer '-std=c++23' -fPIC


all: primeiro app_print app_tipos_main_resto

app_tipos_main_resto: std.pcm resto.pcm main_resto.cpp 
	clang++ -O3 -std=c++23 -stdlib=libc++ -fmodule-file=std=std.pcm -fmodule-file=resto=resto.pcm -o $@ $^

resto.pcm: std.pcm resto.cppm
	clang++ -std=c++23 -stdlib=libc++ -fmodule-file=std=std.pcm --precompile -o $@ $^

run:
	./appMain 

test:
	g++ -fconcepts -g3 -fsanitize=address teste.cpp -o appTeste

run_test:
	./appTeste -d yes

std.pcm: /usr/lib/llvm-19/share/libc++/v1/std.cppm 
	clang++ -std=c++23 -stdlib=libc++ --precompile -o $@ $^

primeiro:
	g++ --std=c++23 main_primeiro.c -o app_primeiro_cpp
	gcc --std=c23   main_primeiro.c -o app_primeiro_c
	g++ --std=c++23 main_primeiro.cpp

app_print: main_print.cpp
	clang++ -O3 -std=c++23 -stdlib=libc++ -fmodule-file=std=std.pcm -o $@ $^