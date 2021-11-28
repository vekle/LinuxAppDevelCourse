cmake_minimum_required(VERSION 3.18)

set(ProjectName "bufTests")
project(${ProjectName})

set(GCC_COVERAGE_COMPILE_FLAGS "-O0 -fprofile-arcs -ftest-coverage")
set(GCC_COVERAGE_LINK_FLAGS "-lgcov")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_library(bufLib buf.c)
link_libraries(bufLib)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(test1 tests/test1.c)
add_executable(test2 tests/test2.c)
add_executable(test3 tests/test3.c)
add_executable(test4 tests/test4.c)
add_executable(test5 tests/test5.c)

include(CTest)
enable_testing()
add_test(TEST1 ${PROJECT_BINARY_DIR}/test1)
add_test(TEST2 ${PROJECT_BINARY_DIR}/test2)
add_test(TEST3 ${PROJECT_BINARY_DIR}/test3)
add_test(TEST4 ${PROJECT_BINARY_DIR}/test4)
add_test(TEST5 ${PROJECT_BINARY_DIR}/test5)
