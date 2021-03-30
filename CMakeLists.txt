cmake_minimum_required(VERSION 3.15)
project(cs261)

set(CMAKE_CXX_STANDARD 14)

include_directories(Assignment_02)

add_executable(test_dynarray Assignment_01/test_dynarray.c Assignment_01/dynarray.c)
add_executable(test_list Assignment_01/test_list.c Assignment_01/test_data.h Assignment_01/list.c)

add_executable(test_queue Assignment_02/test_queue.c Assignment_02/queue.h Assignment_02/queue.c )
add_executable(test_queue_from_stacks Assignment_02/test_queue_from_stacks.c Assignment_02/queue_from_stacks.h Assignment_02/queue_from_stacks.c Assignment_02/stack.h Assignment_02/stack.c)
add_executable(test_stack Assignment_02/test_stack.c Assignment_02/stack.h Assignment_02/stack.c Assignment_02/list.h Assignment_02/list.c)