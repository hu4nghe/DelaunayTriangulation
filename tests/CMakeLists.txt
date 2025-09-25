include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.10.0
)
FetchContent_MakeAvailable(Catch2)


add_executable(parser test_parser.cpp)

target_compile_features(delaunay PRIVATE cxx_std_23)

set_target_properties(delaunay PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    CXX_EXTENSIONS OFF
)

target_link_libraries(parser
    PRIVATE
        csv_parser
        Catch2::Catch2WithMain
)

if(TARGET Catch2::Catch2WithMain)
    target_include_directories(parser
        PRIVATE
            $<TARGET_PROPERTY:Catch2::Catch2WithMain,INTERFACE_INCLUDE_DIRECTORIES>
    )
endif()


include(CTest)
include(Catch)
catch_discover_tests(parser)
