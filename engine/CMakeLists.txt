cmake_minimum_required(VERSION 3.20.1 FATAL_ERROR)

project(engine)
set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
STRING(REGEX REPLACE "/SDL2" "" SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIRS})
include_directories(${PROJ_NAME} ${SDL2_INCLUDE_DIRS})

# Courtesy: https://stackoverflow.com/questions/37817717/sdl2-library-not-found-with-make-but-with-cmake
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(SDL2_Image REQUIRED)
STRING(REGEX REPLACE "/SDL2" "" SDL2_IMAGE_INCLUDE_DIR ${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

# Gather list of header and source files for compilation
file(GLOB_RECURSE MAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine.cpp)
file(GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/**/.cpp)
file(GLOB_RECURSE HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/**/.hpp)
file(GLOB_RECURSE HPP_FILES2 ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine.hpp)

set(ENGINE_INCLUDES ${CMAKE_CURRENT_LIST_DIR}/src/Engine.hpp)

add_library(engine SHARED ${MAIN_FILE} ${CPP_FILES} ${HPP_FILES} ${HPP_FILES2})

target_link_libraries(engine ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_include_directories(engine PUBLIC ${HPP_FILES} ${HPP_FILES2} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR})

set(TESTING_SOURCE
    ${CMAKE_CURRENT_LIST_DIR}/src/testing.cpp
)
add_executable(program ${TESTING_SOURCE})

target_link_libraries(program engine)