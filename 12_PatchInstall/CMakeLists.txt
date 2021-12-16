cmake_minimum_required(VERSION 3.18)

set(ProjectName "Localization")
project(${ProjectName})

add_custom_target(clean_gen rm -rf CMakeF* CMakeC* cmake_* Makefile *.po *.po~ *.pot install_manifest.txt)
add_custom_target(clean_all rm -rf CMakeF* CMakeC* cmake_* Makefile *.po *.po~ *.pot install_manifest.txt guess_num ru_RU.UTF-8)

add_custom_target(translate
                  ALL
                  COMMAND cp ${PROJECT_SOURCE_DIR}/translations/ru.po ${PROJECT_BINARY_DIR}
                  COMMAND xgettext --keyword=_ ${PROJECT_SOURCE_DIR}/guess_num.c -o ${PROJECT_BINARY_DIR}/guess_num.pot
                  COMMAND msgmerge -U ${PROJECT_BINARY_DIR}/ru.po ${PROJECT_BINARY_DIR}/guess_num.pot
                  COMMAND mkdir -p ru_RU.UTF-8/LC_MESSAGES
                  COMMAND msgfmt ${PROJECT_BINARY_DIR}/ru.po -o ru_RU.UTF-8/LC_MESSAGES/guess_num.mo)    

include_directories(${PROJECT_SOURCE_DIR})

add_executable(guess_num guess_num.c)

install(FILES ${PROJECT_BINARY_DIR}/ru_RU.UTF-8/LC_MESSAGES/guess_num.mo
        DESTINATION share/locale/ru_RU.UTF-8/LC_MESSAGES)

install(FILES ${PROJECT_SOURCE_DIR}/man/guess_num.1
        DESTINATION share/man/man1)

install(TARGETS guess_num
        DESTINATION bin)