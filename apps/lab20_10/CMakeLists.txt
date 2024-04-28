cmake_minimum_required(VERSION 3.26)
project(lab20_10 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab20_10 main10.c
        ../../libs/thread_io/thread_io.c
        ../../libs/thread_io/thread_io.h)

target_link_libraries(lab20_10 data_structures)
target_link_libraries(lab20_10 algorithms)
target_link_libraries(lab20_10 string)
target_link_libraries(lab20_10 file_io)
target_link_libraries(lab20_10 thread_io)
