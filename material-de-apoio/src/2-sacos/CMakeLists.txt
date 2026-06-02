cmake_minimum_required(VERSION 4.3.0)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)  
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

# Extrai versao do clang para caminho correto do llvm modules json
execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} --version
    OUTPUT_VARIABLE _clang_version_output
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(REGEX MATCH "clang version ([0-9]+\\.[0-9]+)" _clang_version_match ${_clang_version_output})
set(_full_version ${CMAKE_MATCH_1})
if(_full_version VERSION_LESS 19.0)
    message(FATAL_ERROR "Clang ${_full_version} < 19.0 required")
endif()
string(REGEX REPLACE "\\..*" "" _major_version ${_full_version})
message(STATUS "Versão MAJOR Clang: ${_major_version}")
# CLANG BUG: https://github.com/llvm/llvm-project/issues/172497
set(CMAKE_CXX_STDLIB_MODULES_JSON "/usr/lib/llvm-${_major_version}/lib/libc++.modules.json" CACHE FILEPATH "JSON módulos do libc++ (Clang VERSAO ${_major_version})")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)          # set(CMAKE_CXX_EXTENSIONS OFF)   # UBUNTU 26.04 COM LLVM-21...
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "a9e1cf81-9932-4810-974b-6eccaf14e457")   # OLD
# https://github.com/Kitware/CMake/blob/master/Help/dev/experimental.rst
#set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "a9e1cf81-9932-4810-974b-6eccaf14e457")
# set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444") # 4.1
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b") # 4.3

set(CMAKE_CXX_MODULE_STD 1)

project(autograding_project VERSION 0.1.0 LANGUAGES CXX)

message(STATUS "Compilador C++: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Versão do Compilador: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Versão MAJOR do Compilador: ${_major_version}")

add_library(saco_tad)
target_sources(saco_tad  PUBLIC  FILE_SET CXX_MODULES FILES   src/SacoTAD.cppm)

add_library(saco_lista_encadeada)
target_sources(saco_lista_encadeada  PUBLIC  FILE_SET CXX_MODULES FILES   src/SacoListaEncadeada.cppm)
target_link_libraries(saco_lista_encadeada PRIVATE saco_tad)

add_library(saco_vetor)
target_sources(saco_vetor  PUBLIC  FILE_SET CXX_MODULES FILES   src/SacoVetor.cppm)
target_link_libraries(saco_vetor PRIVATE saco_tad)

add_executable(app_saco src/main.cpp)
target_link_libraries(app_saco PRIVATE saco_tad saco_lista_encadeada saco_vetor)
