cmake_minimum_required(VERSION 3.26)
project(lab C)

set(CMAKE_C_STANDARD 11)

add_executable(lab main.c)

add_subdirectory(libs)
target_link_libraries(lab data_structures)
target_link_libraries(lab algorithms)
target_link_libraries(lab string)
