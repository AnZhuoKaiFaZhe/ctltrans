cmake_minimum_required(VERSION 3.17)
project(ctl2snf)
set(CMAKE_CXX_STANDARD 14)

find_package(BISON)
find_package(FLEX)

BISON_TARGET(Parser src/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(Scanner src/scanner.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        src
        include
)

add_executable(ctl2snf
        src/main.cpp
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Scanner_OUTPUTS}
        src/types.cpp
        )