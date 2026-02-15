cmake_minimum_required(VERSION 4.2)
project(flappy_bird LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Use modern raylib version (CMake 4 compatible)
set(RAYLIB_VERSION 5.5)

FetchContent_Declare(raylib
  URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# Disable building raylib examples
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()



FetchContent_MakeAvailable(raylib)

add_executable(${PROJECT_NAME}
  src/Main.c
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Silence GCC stringop overflow warnings coming from raylib's external deps
if (CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(raylib PRIVATE -Wno-stringop-overflow)
endif()

# MacOS frameworks (still required)
if(APPLE)
  target_link_libraries(${PROJECT_NAME} PRIVATE
    "-framework IOKit"
    "-framework Cocoa"
    "-framework OpenGL"
  )
endif()
