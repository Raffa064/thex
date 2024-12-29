cmake_minimum_required(VERSION 3.31.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(FaskTest)

find_package(Curses REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(thex "${SOURCES}")

target_include_directories(thex PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(thex PRIVATE ${CURSES_LIBRARIES})
target_include_directories(thex PRIVATE ${CURSES_INCLUDE_DIR})
