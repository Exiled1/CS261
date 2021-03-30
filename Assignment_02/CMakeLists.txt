cmake_minimum_required(VERSION 3.17)
project(Assignment_02 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(TestQueue test_queue.c queue.c dynarray.c)

add_executable(test_queue_from_stacks test_queue_from_stacks.c queue_from_stacks.c stack.c list.c)

add_executable(test_stack test_stack.c stack.c list.c)

add_executable(queue_from_stacks queue_from_stacks.c stack.c list.c)

