cmake_minimum_required(VERSION 3.20)
project(DelaunayTriangulation VERSION 1.0)

# Specify C23 standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find all header and source files automatically
aux_source_directory(src SOURCES)
aux_source_directory(include HEADERS)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Add include directory
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link against the math library (libm)
target_link_libraries(${PROJECT_NAME} PRIVATE m)