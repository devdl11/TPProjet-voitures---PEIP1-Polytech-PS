cmake_minimum_required(VERSION 3.22.1)
project(mainDir)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

add_executable(mainDir main.cpp src/nasch.h src/nasch.cpp tests/tests.cpp tests/tests.h src/tracing.cpp src/tracing.h tests/nasch_test.cpp tests/nasch_test.h)

set_target_properties(mainDir PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}"
        )

add_test(NAME run_test COMMAND mainDir)