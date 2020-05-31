cmake_minimum_required(VERSION 3.0)

project(generic_programming)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} --std=c++17)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_compile_options(-Wall -Wextra -O2)

add_executable(parameters parameters.cpp)
add_executable(class_templates class_templates.cpp)
add_executable(compile_time_programming compile_time_programming.cpp)
add_executable(expression_templates expression_templates.cpp)
add_executable(full_specialization full_specialization.cpp)
add_executable(function_templates function_templates.cpp)
add_executable(inheritance inheritance.cpp)
add_executable(numeric_array numeric_array.cpp)
add_executable(partial_specialization partial_specialization.cpp)
add_executable(variadic variadic.cpp)
