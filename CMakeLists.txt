cmake_minimum_required(VERSION 2.8)

# Turn on C++ 14 support
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# All Warnings # -Werror -pedantic
set(WARNING_FLAGS "-Wall -Wextra ")
set(SHARED_FLAGS "${WARNING_FLAGS}")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    message(STATUS "Using Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SHARED_FLAGS} -std=c++14 -stdlib=libc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message(STATUS "Using GCC")
    set(CMAKE_CXX_FLAGS "-std=c++11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SHARED_FLAGS} -std=c++14 -pthread")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
endif()

add_executable(circular_queue_test main.cpp circular_queue.cpp)
