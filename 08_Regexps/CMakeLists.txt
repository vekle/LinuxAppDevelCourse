cmake_minimum_required(VERSION 3.18)

set(ProjectName "esub")
project(${ProjectName})

### Binary

add_executable(${ProjectName} main.c)

target_link_libraries(${ProjectName} PUBLIC ${EXTRA_LIBS})

target_include_directories(${ProjectName} PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

### Testing

configure_file(test.sh test_bin.sh COPYONLY)

enable_testing()
add_test(Test ${PROJECT_BINARY_DIR}/test_bin.sh)