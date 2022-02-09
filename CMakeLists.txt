cmake_minimum_required(VERSION 3.13)

project(test LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    test.cpp
    Tree.h
    Tree.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(TEST_INPUT_FILES
    modify.txt
    read.txt
    write.txt
)

file(COPY ${TEST_INPUT_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
