cmake_minimum_required(VERSION 3.31.0)

# Build options
option(DEBUG OFF) # Disable compiler optimizations for faster build
option(OPTIMIZE OFF) # Enables a lot of optimizations

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Necessary for LSP completion

if(DEBUG)
  message(WARNING "Using DEBUG build option")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -g")

  if(OPTIMIZE)
    message(WARNING "Can't use OPTIMIZE with debug option")
  endif()
elseif(OPTIMIZE)
  message(WARNING "Using agressive optimizations")
  set(CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} -O3 -Werror -funroll-loops -flto -fvisibility=hidden -ftree-vectorize -fno-rtti -fno-common"
  )
endif()

message("  * CXX_FLAGS: '${CMAKE_CXX_FLAGS}'")

# Project sources and targets
project(THex)
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(thex "${SOURCES}")
target_include_directories(thex PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Add inicpp library
add_subdirectory(./inicpp)

# Add ncurses library
find_package(Curses REQUIRED)

target_link_libraries(thex PRIVATE ${CURSES_LIBRARIES} ${INICPP_LIBRARIES})
target_include_directories(thex PRIVATE ${CURSES_INCLUDE_DIR})

if(ANDROID)
  set(CMAKE_INSTALL_PREFIX "/data/data/com.termux/files/usr/")
else()
  message(
    WARNING
      "This project was not developed or natively tested for your operating system. There may be compatibility issues."
  )

  if(WIN32)
    set(CMAKE_INSTALL_PREFIX "C:/Program Files/thex")
  elseif(UNIX)
    set(CMAKE_INSTALL_PREFIX "/usr/local")
  else()
    set(CMAKE_INSTALL_PREFIX "/opt/thex")
  endif()
endif()

message("  * Installation prefix: " ${CMAKE_INSTALL_PREFIX})
install(TARGETS thex DESTINATION bin)
