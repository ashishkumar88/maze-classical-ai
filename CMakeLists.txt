cmake_minimum_required(VERSION 3.14...3.27)

project(MazeSolver
        VERSION 1.0
        DESCRIPTION "Algorithms the solve different 2D maze scenarios."
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Set the output directory for the build executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set the output directory for the build install
set(INSTALL_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/install)

# add the subdirectories
add_subdirectory(src)
add_subdirectory(apps)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_subdirectory(tests)
