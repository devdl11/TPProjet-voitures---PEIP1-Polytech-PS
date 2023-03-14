cmake_minimum_required(VERSION 3.22.1)
project(mainDir)

set(CMAKE_CXX_STANDARD 17)

add_executable(mainDir main.cpp src/nasch.h src/nasch.cpp tests/tests.cpp tests/tests.h src/tracing.cpp src/tracing.h tests/nasch_test.cpp tests/nasch_test.h)
