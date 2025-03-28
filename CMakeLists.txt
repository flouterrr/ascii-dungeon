cmake_minimum_required(VERSION 3.30)


project("ascii_dungeon")
set(LANGUAGE C)
set(CMAKE_C_STANDARD 11)

file(GLOB SourceFiles CONFIGURE_DEPENDS "src/*.c")

add_executable(${CMAKE_PROJECT_NAME} ${SourceFiles})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "src/")
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC PROJECT_ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}/")

