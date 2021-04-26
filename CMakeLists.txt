cmake_minimum_required(VERSION 3.20.1 FATAL_ERROR)
project(MAIN1 VERSION 1.0)


set(ENV{LIB_PATH} "")

add_subdirectory(engine)
add_subdirectory(projects)