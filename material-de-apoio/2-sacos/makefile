all: make_gcc  cmake_clang

make_gcc:
	g++ -std=c++23 -fmodules -fsearch-include-path bits/std.cc  src/SacoTAD.cppm src/SacoVetor.cppm  src/SacoListaEncadeada.cppm  src/main.cpp

cmake_clang:
	python3 -m pip install -v "cmake==4.3" --break-system-packages
	mkdir -p build
	cd build && cmake .. -GNinja && ninja

force_reinstall_cmake:
	python3 -m pip install --force-reinstall -v "cmake==4.3" --break-system-packages