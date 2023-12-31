# compiler options
target_compile_features(MazeSolver PRIVATE cxx_std_17)

# Explicitly list the test source code and headers.
set(${PROJECT_NAME}_TEST_GRID
    test_grid.cpp
)

# Link with gtest or gtest_main as needed.
add_executable(test_grid ${${PROJECT_NAME}_TEST_GRID} ${HEADER_LIST})
target_link_libraries(test_grid gtest_main ${PROJECT_NAME}Lib)

# Add custom command post build, this ensures tests are run after compilation
add_custom_command(
    TARGET test_grid
    COMMENT "Run grid tests"
    POST_BUILD
    COMMAND test_grid
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/tests/"
)

