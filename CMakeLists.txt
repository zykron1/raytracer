cmake_minimum_required(VERSION 3.16)

project(Raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(Raytracer ${SOURCES})

target_include_directories(Raytracer PRIVATE
    src
)

target_compile_options(Raytracer PRIVATE
    -O3
)

# Produce a self-contained Windows executable
if(MINGW)
    target_link_options(Raytracer PRIVATE
        -static
        -static-libgcc
        -static-libstdc++
    )
endif()
