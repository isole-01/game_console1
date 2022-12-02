cmake_minimum_required(VERSION 3.14)
project(v_1 C)

set(CMAKE_C_STANDARD 99)

add_executable(v_1 main.c game_console.h file.c move.c ai.c graphics.c)