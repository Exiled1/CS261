cmake_minimum_required(VERSION 3.17)
project(recitation_5 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(recitation_5
        dynarray.c
        dynarray.h
        time_dynarray_insert.c)
