cmake_minimum_required(VERSION 3.20)
project(tick C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(tick ${SOURCES})

add_subdirectory(src)

find_package(raylib REQUIRED)
target_link_libraries(tick PRIVATE raylib)

if(APPLE)
  target_link_libraries(tick PRIVATE
    "-framework Cocoa"
    "-framework IOKit"
    "-framework OpenGL"
  )
endif()

target_include_directories(tick PRIVATE src)
