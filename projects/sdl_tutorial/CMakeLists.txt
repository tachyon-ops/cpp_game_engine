cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

set(PROJ_NAME "HandmadeHero")

project (${PROJ_NAME})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../engine/src)

# Gather list of header and source files for compilation
file(GLOB_RECURSE MAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
file(GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp)
file(GLOB_RECURSE HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.hpp)

# Build project, give it a name and includes list of file to be compiled
add_executable(${PROJ_NAME} ${MAIN_FILE} ${CPP_FILES} ${HPP_FILES})

target_include_directories (${PROJ_NAME} 
    PUBLIC ${SFML_INCLUDE_DIR}
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_custom_command(
    TARGET ${PROJ_NAME} POST_BUILD
    COMMAND cp -rf
        $ENV{LIB_PATH}
        ${PROJECT_BINARY_DIR}
)

target_link_libraries (${PROJ_NAME} engine)

