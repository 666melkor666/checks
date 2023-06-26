cmake_minimum_required(VERSION 3.23)
project(clang_tidy_check)

set(CMAKE_CXX_STANDARD 23)

find_package(Clang REQUIRED)

add_library(clang_tidy_check SHARED
        module.cpp
        lambda_in_parenthesis.cpp
        return_statement_in_parenthesis.cpp)

target_include_directories(clang_tidy_check PRIVATE ${CLANG_INCLUDE_DIRS})
target_link_libraries(clang_tidy_check
        PRIVATE
        clang-tidy
)