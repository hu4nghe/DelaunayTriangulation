cmake_minimum_required(VERSION 3.28)
project(DelaunayTriangulation VERSION 1.0)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(Graph STATIC src/Graph.c)
add_executable(DelaunayExecutable src/Delaunay.c)

target_compile_features(DelaunayExecutable PRIVATE c_std_23)

set_target_properties(DelaunayExecutable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)


target_link_libraries(DelaunayExecutable PRIVATE Graph)

target_include_directories(Graph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(DelaunayExecutable PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(UNIX)
    target_link_libraries(DelaunayExecutable PRIVATE m)
endif()