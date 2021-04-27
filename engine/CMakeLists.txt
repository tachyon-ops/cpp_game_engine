cmake_minimum_required(VERSION 3.20.1 FATAL_ERROR)

# message("CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
# if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
#   set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -undefined dynamic_lookup")
# elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
#     set(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -undefined dynamic_lookup")
# endif()

project(engine)
set(CMAKE_CXX_STANDARD 17)

# Courtesy of https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
find_library(SDL2_LIBRARY NAME SDL2 REQUIRED)
STRING(REGEX REPLACE "/SDL2" "" SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIRS})
include_directories(${PROJ_NAME} ${SDL2_INCLUDE_DIRS})

# Courtesy: https://stackoverflow.com/questions/37817717/sdl2-library-not-found-with-make-but-with-cmake
find_package(SDL2_Image REQUIRED)
STRING(REGEX REPLACE "/SDL2" "" SDL2_IMAGE_INCLUDE_DIR ${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

# Gather list of header and source files for compilation
file(GLOB_RECURSE TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/testing.cpp)
file(GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp)
file(GLOB_RECURSE HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.hpp)

# MAIN LIB
set(engineSource ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine/Engine.cpp)
set(texManSource ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine/TextureManager.cpp)

add_library(engine SHARED ${engineSource} ${texManSource})
target_link_libraries(engine
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARY}
)
target_include_directories(engine PUBLIC ${HPP_FILES} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR})

set(SDL2_LIB_FILE ${SDL2_LIBRARY})
STRING(REGEX REPLACE "-framework Cocoa" "" SDL2_LIB_FILE ${SDL2_LIB_FILE})

set(LIB_OUT ${PROJECT_BINARY_DIR}/bin)
add_custom_command(
    TARGET engine POST_BUILD
    COMMAND mkdir -p ${LIB_OUT}
)

add_custom_command(
    TARGET engine POST_BUILD
    COMMAND install -C -m 775 -o $ENV{USER}
        ${SDL2_IMAGE_LIBRARY}
        ${LIB_OUT}
)

add_custom_command(
    TARGET engine POST_BUILD
    COMMAND install -C -m 775 -o $ENV{USER}
        ${SDL2_LIB_FILE}
        ${LIB_OUT}
)

add_custom_command(
    TARGET engine POST_BUILD
    COMMAND install -C -m 775 -o $ENV{USER}
        libengine.dylib
        ${LIB_OUT}
)



get_directory_property(hasParent PARENT_DIRECTORY)
if(hasParent)
    message(STATUS "Has a parent scope. ${LIB_OUT}")
    set(ENV{LIB_PATH} ${LIB_OUT})
else()
  message(STATUS "Doesn't have a parent scope.")
endif()


set(TESTING_SOURCE
    ${CMAKE_CURRENT_LIST_DIR}/src/testing.cpp
)
add_executable(EngineTest ${TESTING_SOURCE} ${CPP_FILES})

target_link_libraries(EngineTest
    # engine
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARY}
)

# COPY TEST ASSETS
file(GLOB_RECURSE ${CMAKE_CURRENT_LIST_DIR}/assets ${PROJECT_BINARY_DIR})
add_custom_command(
    TARGET EngineTest POST_BUILD
    COMMAND cp -rf
        ${CMAKE_CURRENT_LIST_DIR}/assets
        ${PROJECT_BINARY_DIR}
)