cmake_minimum_required(VERSION 3.21.3)

project(multi_thread_queue_cpp
    VERSION 1.0
    DESCRIPTION "Multi-Thread access to Queue class"
    LANGUAGES CXX)

add_executable(multi_thread_queue_cpp
			  src/main.cpp 
			  src/Queue.h
)

target_compile_features(multi_thread_queue_cpp PRIVATE cxx_std_11)

target_compile_options(multi_thread_queue_cpp PRIVATE -Wall -Wextra -Wpedantic)

target_link_libraries( multi_thread_queue_cpp pthread )
