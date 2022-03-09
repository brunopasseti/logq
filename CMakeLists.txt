cmake_minimum_required(VERSION 3.2)


project(logq)


add_executable(logq src/main.cpp)
target_link_libraries(logq PRIVATE nlohmann_json::nlohmann_json)

FetchContent_Declare(glpk URL https://ftp.gnu.org/gnu/glpk/glpk-5.0.tar.gz)
FetchContent_MakeAvailable(glpk)
target_link_libraries(logq PRIVATE glpk)
