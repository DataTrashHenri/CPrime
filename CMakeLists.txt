cmake_minimum_required(VERSION 3.31)
project(PrimeTest C)

set(CMAKE_C_STANDARD 11)

add_executable(PrimeTest main.c
        chunk.c
        chunk.h
        buffer.c
        buffer.h
)
