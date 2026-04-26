cmake_minimum_required(VERSION 4.2)

project(snake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(snake)

target_sources(snake PRIVATE src/main.c)

find_package(SDL3 REQUIRED)

target_link_libraries(snake PRIVATE SDL3::SDL3)
target_compile_definitions(snake PRIVATE SDL_MAIN_USE_CALLBACKS)
target_link_options(snake PRIVATE -static)

# Copy SDL3.dll next to the built .exe so it can be found at runtime
add_custom_command(TARGET snake POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE_DIR:snake>
)