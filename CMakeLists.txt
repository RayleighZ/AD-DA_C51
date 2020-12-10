cmake_minimum_required(VERSION 3.16)
project(ADDA C)

set(CMAKE_C_STANDARD 99)

add_executable(ADDA AddaMain.c SPI_TOOL.c SPI_TOOL.h)