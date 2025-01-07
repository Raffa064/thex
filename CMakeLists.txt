cmake_minimum_required(VERSION 3.31.0)

# Build options
option(DEBUG OFF) # Disable compiler optimizations for faster build

set(CMAKE_CXX_STANDARD 14) 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Necessary for LSP completion

if(DEBUG)
  message("Using DEBUG build option")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -g")
endif()

# Project sources and targets
project(FaskTest)
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(thex "${SOURCES}")
target_include_directories(thex PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Include ncurses library
find_package(Curses REQUIRED)
target_link_libraries(thex PRIVATE ${CURSES_LIBRARIES})
target_include_directories(thex PRIVATE ${CURSES_INCLUDE_DIR})
