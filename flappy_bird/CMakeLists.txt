cmake_minimum_required(VERSION 3.24)
project(flappy_bird)


set(CMAKE_CXX_STANDARD 11)


include(FetchContent)

set(RAYLIB_VERSION 4.5.0)


FetchContent_Declare(
  raylib
  URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
      FIND_PACKAGE_ARGS
      ${RAYLIB_VERSION}
      EXACT)

set(BUILD_EXAMPLES
    OFF
    CACHE INTERNAL "")


FetchContent_MakeAvailable(raylib)

set(SOURCE_FILES src/Main.c)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})


target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if(APPLE)
  target_link_libraries(${PROJECT_NAME} "-framework IOKit")
  target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
  target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
