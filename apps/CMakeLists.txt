# add the executable
add_executable(${PROJECT_NAME} solver.cpp)

# compiler options
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# link the executable to the libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}Lib)