add_library(GetlineCMD getline_cmd.c)

target_include_directories(GetlineCMD
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )