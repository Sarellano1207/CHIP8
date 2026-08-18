cmake_minimum_required(VERSION 3.16)
project(chip8 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

add_executable(chip8
    src/main.cpp
    src/chip8.cpp
    src/display.cpp
)

target_compile_options(chip8 PRIVATE -Wall -Wextra)
target_link_libraries(chip8 PRIVATE raylib)