cmake_minimum_required(VERSION 3.22)
#
#set(CMAKE_CXX_COMPILER "/usr/bin/g++-12")
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++-16")
#
project(curso-ed-i-project LANGUAGES CXX VERSION 0.0.1)
#
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
#
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    SET(CMAKE_CXX_FLAGS "-stdlib=libc++")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
endif()

Include(FetchContent)

# ==================
# external libraries
# ------------------
# add_subdirectory(external/fmt-9.1.0)
FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG 9.1.0)
FetchContent_MakeAvailable(fmt)
#
# add_subdirectory(external/scnlib-1.1.2)
FetchContent_Declare(scn GIT_REPOSITORY https://github.com/eliaskosunen/scnlib.git GIT_TAG v1.1.2)
FetchContent_MakeAvailable(scn)
#
add_subdirectory(material/1-revisao-tipos)
add_subdirectory(material/3-pilhas)

