cmake_minimum_required(VERSION 3.10)
project(calculator C)
set(CMAKE_C_STANDARD 11)

add_executable(calculator main.c math_utils.c)