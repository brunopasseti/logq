cmake_minimum_required(VERSION 3.20)

project(logq VERSION 0.0.1)

# Add symbolic link to resources folder in build
add_custom_target(instances)
FILE(TO_NATIVE_PATH "${PROJECT_SOURCE_DIR}/instances" source)
FILE(TO_NATIVE_PATH "${PROJECT_BINARY_DIR}/instances" destination)

add_custom_command(
TARGET instances POST_BUILD
COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
DEPENDS ${destination}
COMMENT "symbolic link instances folder from ${source} => ${destination}"
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
include(ExternalProject)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(logq src/main.cpp)
add_dependencies(logq instances)
target_link_libraries(logq PRIVATE nlohmann_json::nlohmann_json)

FetchContent_Declare(glpk URL https://ftp.gnu.org/gnu/glpk/glpk-5.0.tar.gz)
FetchContent_MakeAvailable(glpk)
target_link_libraries(logq PRIVATE glpk)

target_include_directories(logq PRIVATE /home/brunopasseti/Downloads/coin-or/CoinUtils/src /home/brunopasseti/Downloads/coin-or/Osi/src/Osi /home/brunopasseti/Downloads/coin-or/Osi/src/OsiGlpk)

# find_library(osi NAMES Osi PATHS /home/brunopasseti/Downloads/coin-or/dist/lib)
# target_link_libraries(logq PRIVATE Osi)
# LD_LIBRARY_PATH=/home/brunopasseti/Downloads/coin-or/dist/lib