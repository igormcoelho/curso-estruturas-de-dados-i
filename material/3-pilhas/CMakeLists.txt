cmake_minimum_required(VERSION 3.22)
#
project(ed-i-3-pilhas-project LANGUAGES CXX VERSION 0.0.1)
#
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
#
Include(FetchContent)
FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG 9.1.0)
FetchContent_MakeAvailable(fmt)
#
add_executable(app_pilhas main_pilhas.cpp)
target_link_libraries(app_pilhas PRIVATE fmt)
#
add_executable(app_pilha_stl main_pilha_stl.cpp)