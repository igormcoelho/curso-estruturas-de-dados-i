cmake_minimum_required(VERSION 3.22)
#
project(ed-i-1-tipos-project LANGUAGES CXX VERSION 0.0.1)
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
add_executable(app_tipos_main main.cpp)
target_link_libraries(app_tipos_main PRIVATE fmt)
#
add_executable(app_tipos_main_resto main_resto.cpp)
target_link_libraries(app_tipos_main_resto PRIVATE fmt)

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