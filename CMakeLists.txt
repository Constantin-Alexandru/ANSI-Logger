cmake_minimum_required(VERSION "3.26.2")

add_subdirectory("./ANSI-Libray")

project(ANSI-Logger)
add_library(ANSI-Logger INTERFACE)
target_include_directories(ANSI-Logger INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(SyncStream PRIVATE ANSI-Library)