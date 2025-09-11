# README.md

# Delaunay Triangulation Project

This project implements the Delaunay triangulation algorithm using a graph data structure. It consists of a static library for the graph and an executable for the Delaunay triangulation.

## Project Structure

- `src/`: Contains the source files.
  - `Delaunay.c`: Implementation of the Delaunay triangulation algorithm.
  - `Graph.c`: Implementation of the graph data structure.
  
- `include/`: Contains the header files.
  - `Delaunay.h`: Function declarations for the Delaunay triangulation.
  - `Graph.h`: Function declarations for the graph data structure.
  - `List.h`: Declarations for list structures used in the project.

- `CMakeLists.txt`: CMake configuration file for building the project.
- `README.md`: Documentation for the project.

## Building the Project

To build the project, follow these steps:

1. Navigate to the project directory:
   ```
   cd path/to/DelaunayTriangulation
   ```

2. Create a build directory:
   ```
   mkdir build
   cd build
   ```

3. Run CMake to configure the project:
   ```
   cmake ..
   ```

4. Build the project:
   ```
   cmake --build .
   ```

## License

HUANG He
he.huang@utt.fr