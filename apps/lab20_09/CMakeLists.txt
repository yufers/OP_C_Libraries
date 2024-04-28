cmake_minimum_required(VERSION 3.26)
project(lab20_09 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab20_09 main9.c
        ../../libs/thread_io/thread_io.c
        ../../libs/thread_io/thread_io.h)

target_link_libraries(lab20_09 data_structures)
target_link_libraries(lab20_09 algorithms)
target_link_libraries(lab20_09 string)
target_link_libraries(lab20_09 file_io)
target_link_libraries(lab20_09 thread_io)
