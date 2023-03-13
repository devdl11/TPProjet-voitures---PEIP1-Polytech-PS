cmake_minimum_required(VERSION 3.24)
project(mainDir)

set(CMAKE_CXX_STANDARD 17)

add_executable(mainDir main.cpp src/nasch.h src/nasch.cpp src/tests.cpp src/tests.h src/tracing.cpp src/tracing.h)
