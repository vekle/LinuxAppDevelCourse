cmake_minimum_required(VERSION 3.18)

set(ProjectName "rhasher")
project(${ProjectName})

### Libs

option(USE_READLINE "Use readline function" ON)

find_library(RhashLib rhash REQUIRED)
list(APPEND EXTRA_LIBS ${RhashLib})

find_library(ReadlineLib readline)
if(USE_READLINE AND ReadlineLib)
    add_subdirectory(readline_cmd)
    list(APPEND EXTRA_LIBS ReadlineCMD)
else()
    add_subdirectory(getline_cmd)
    list(APPEND EXTRA_LIBS GetlineCMD)
endif()

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