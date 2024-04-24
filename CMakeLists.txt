cmake_minimum_required(VERSION 3.26)
project(lab C)

set(CMAKE_C_STANDARD 11)

add_executable(lab main.c
        libs/file_io/file_io.c
        libs/file_io/file_io.h
        libs/file_io/file_io_test.c
        libs/file_io/file_io_test.h
        libs/thread_io/thread_io.c
        libs/thread_io/thread_io.h
        libs/thread_io/thread_io_test.c
        libs/thread_io/thread_io_test.h)

add_subdirectory(libs)

target_link_libraries(lab data_structures)
target_link_libraries(lab algorithms)
target_link_libraries(lab string)
target_link_libraries(lab file_io)
target_link_libraries(lab thread_io)
