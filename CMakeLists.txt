cmake_minimum_required(VERSION 3.28)
project(DelaunayTriangulation VERSION 1.0)

add_subdirectory(modules/csv_parser)
add_subdirectory(modules/delaunay)
enable_testing()
add_subdirectory(tests)
