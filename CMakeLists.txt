cmake_minimum_required(VERSION 2.8)
project(pjc-lab5)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wl,--no-as-needed  -lpthread ${CMAKE_CXX_FLAGS}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(IntBufferTest
	 intBuffer_test.cpp
	 pro-consumer.cpp
	 pro-consumer.h

)
