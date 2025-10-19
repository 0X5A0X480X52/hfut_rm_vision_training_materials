cmake_minimum_required(VERSION 3.10)

project(StudentManagement)

set(CMAKE_C_STANDARD 11)

# 添加可执行文件

# 设置编译选项 (通过后面的条件分支应用)
include_directories(${CMAKE_SOURCE_DIR}/includes)

# 将 src 目录下的所有 .c 源文件添加到可执行文件中
add_executable(student_system 
    ${CMAKE_SOURCE_DIR}/src/main.c
    ${CMAKE_SOURCE_DIR}/src/student.c
    ${CMAKE_SOURCE_DIR}/src/file_utils.c
)

# 根据编译器选择合适的警告选项
target_compile_options(student_system PRIVATE -Wall -Wextra)