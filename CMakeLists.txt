cmake_minimum_required(VERSION 3.20.1 FATAL_ERROR)
project(MAIN1 VERSION 1.0)

set(PROJ_MAJOR_VERSION "0")
set(PROJ_MINOR_VERSION "0")
set(PROJ_PATCH_VERSION "1")
set(PROJ_VERSION_STRING "${PROJ_MAJOR_VERSION}.${PROJ_MINOR_VERSION}.${PROJ_PATCH_VERSION}")

set (CMAKE_CXX_STANDARD 17)


set(ENV{LIB_PATH} "")

add_subdirectory(engine)
add_subdirectory(projects)