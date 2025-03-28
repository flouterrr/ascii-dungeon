cmake_minimum_required(VERSION 3.30)

project("ascii_dungeon" LANGUAGE C)
file(GLOB SourceFiles CMAKE_CONFIGURE_DEPENDS "/src/*.c")
add_executable(${CMAKE_PROJECT_NAME} ${SourceFiles})

