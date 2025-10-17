cmake_minimum_required(VERSION 3.5)
project(flappybird.ver.2.0 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

include_directories(./head)

aux_source_directory(head HEADFILES)
aux_source_directory(src SRCFILES)

add_executable(flappybird.ver.0.2 main.cpp ${HEADFILES} ${SRCFILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
