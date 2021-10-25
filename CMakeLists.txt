cmake_minimum_required(VERSION 3.21.3)

project(multi_thread_queue_cpp
    VERSION 1.0
    DESCRIPTION "Multi-Thread access to Queue class"
    LANGUAGES CXX)

add_executable(multi_thread_queue_cpp
			  src/main.cpp 
			  src/Queue.h
)

# Compiler needs to be compatible with C++11
target_compile_features(multi_thread_queue_cpp PRIVATE cxx_std_11)

# Platform dependency
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_options(multi_thread_queue_cpp PRIVATE /W4)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(multi_thread_queue_cpp PRIVATE -Wall -Wextra -Wpedantic)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # other macOS-specific flags for Clang
endif()

# Find PTHREAD library and throw error if not available
find_library(LIBRARY_PTHREAD pthread)
if (LIBRARY_PTHREAD)
    target_link_libraries(multi_thread_queue_cpp PRIVATE ${LIBRARY_PTHREAD} )
else()
    # throw an error or enable compilation without the library
endif()

# Fetch GoogleTest git package
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/16f637fbf4ffc3f7a01fa4eceb7906634565242f.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# GoogleTest config
enable_testing()

add_executable(
  queue_test
  src/tests/queue_test.cc
)
target_link_libraries(
  queue_test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(queue_test)
