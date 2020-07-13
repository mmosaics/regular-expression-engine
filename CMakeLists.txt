cmake_minimum_required(VERSION 3.16)
project(regular_expression_engine)

set(CMAKE_CXX_STANDARD 11)

add_executable(regular_expression_engine main.cpp lexical_analyzer/Token.h lexical_analyzer/SimpleToken.cpp lexical_analyzer/SimpleToken.h)