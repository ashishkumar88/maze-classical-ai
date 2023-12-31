# scan for all header files
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${${PROJECT_NAME}_SOURCE_DIR}/include/*.hpp")

# add the library
add_library(${PROJECT_NAME}Lib STATIC grid.cpp graph.cpp utils.cpp ${HEADER_LIST})

# set the include directories
target_include_directories(${PROJECT_NAME}Lib PUBLIC "${${PROJECT_NAME}_SOURCE_DIR}/include")

# compile options
target_compile_features(${PROJECT_NAME}Lib PUBLIC cxx_std_17)