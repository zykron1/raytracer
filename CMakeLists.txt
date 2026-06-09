cmake_minimum_required(VERSION 3.16)

project(Raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(Raytracer ${SOURCES})

find_package(OpenMP REQUIRED)
target_link_libraries(Raytracer OpenMP::OpenMP_CXX)

target_include_directories(Raytracer PRIVATE src -O3)
