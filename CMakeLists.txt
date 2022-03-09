cmake_minimum_required(VERSION 3.20)


project(logq VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
include(ExternalProject)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(logq src/main.cpp)
target_link_libraries(logq PRIVATE nlohmann_json::nlohmann_json)

FetchContent_Declare(glpk URL https://ftp.gnu.org/gnu/glpk/glpk-5.0.tar.gz)
FetchContent_MakeAvailable(glpk)
target_link_libraries(logq PRIVATE glpk)
