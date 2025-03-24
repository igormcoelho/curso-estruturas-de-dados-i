cmake_minimum_required(VERSION 4.0.0)
# set(CMAKE_CXX_COMPILER /usr/bin/g++-15)
# set(CMAKE_CXX_COMPILER /usr/bin/clang++-19)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "a9e1cf81-9932-4810-974b-6eccaf14e457")
set(CMAKE_CXX_MODULE_STD 1)

project(hello_world_project VERSION 0.1.0 LANGUAGES CXX)


add_library(resto)
target_sources(resto  PUBLIC  FILE_SET CXX_MODULES FILES   resto.cppm)
#
add_executable(app_tipos_main_resto main_resto.cpp)
target_link_libraries(app_tipos_main_resto PRIVATE resto)

#
add_executable(app_tipos_main main.cpp)

#==========
#  TESTS
#----------
# add_subdirectory(test/external/Catch2/)
FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG v3.3.1)
FetchContent_MakeAvailable(Catch2)
#
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
#
add_executable(app_tipos_teste teste.cpp)
target_link_libraries(app_tipos_teste PRIVATE fmt Catch2::Catch2WithMain)
catch_discover_tests(app_tipos_teste)