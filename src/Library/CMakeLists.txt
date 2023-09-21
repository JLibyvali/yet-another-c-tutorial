cmake_minimum_required(VERSION 3.20)
project(my_library)
# https://cmake.org/cmake/help/latest/variable/CMAKE_EXPORT_COMPILE_COMMANDS.html
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(a)
add_subdirectory(b)

add_executable(main_cpp main.cpp)
target_include_directories(main_cpp PUBLIC a b)
target_link_libraries(main_cpp a b)
