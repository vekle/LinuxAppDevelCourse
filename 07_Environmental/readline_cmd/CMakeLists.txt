add_library(ReadlineCMD getline_cmd.c)

target_link_libraries(ReadlineCMD readline)

target_include_directories(ReadlineCMD
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )