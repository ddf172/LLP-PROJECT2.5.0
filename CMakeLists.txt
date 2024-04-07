cmake_minimum_required(VERSION 3.29)
project(LLP_PROJECT_2_5_0 C)

set(CMAKE_C_STANDARD 11)

add_executable(LLP_PROJECT_2_5_0 main.c
        Headers/Bitmap.h
        Bitmap.c
        Headers/FileProcessing.h
        FileProcessing.c
        Headers/Mandelbrot.h
        Headers/Mandelbrot.c)

target_link_libraries(LLP_PROJECT_2_5_0 m)