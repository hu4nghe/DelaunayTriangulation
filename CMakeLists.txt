cmake_minimum_required(VERSION 3.28)
project(DelaunayTriangulation VERSION 1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++23")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")

add_subdirectory(modules/csv_parser)
add_subdirectory(modules/delaunay)
enable_testing()
add_subdirectory(tests)
