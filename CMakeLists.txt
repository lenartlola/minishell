cmake_minimum_required(VERSION 3.20)
project(miniRT C)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_C_STANDARD 99)
add_compile_options(-Wall -Werror -Wextra)

SET(LIBS ft)
SET(LIBS ${LIBS})
include_directories(libs/libft/incs incs)
link_directories(libs/libft)

add_executable(
        minishell
        srcs/main.c
)

TARGET_LINK_LIBRARIES(minishell ${LIBS})