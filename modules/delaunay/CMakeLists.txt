add_executable(delaunay src/delaunay.cpp)

target_compile_features(delaunay PRIVATE cxx_std_23)

set_target_properties(delaunay PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    CXX_EXTENSIONS OFF
)

target_link_libraries(delaunay
    PRIVATE
    csv_parser
)

