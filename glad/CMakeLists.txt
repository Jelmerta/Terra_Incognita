cmake_minimum_required(VERSION 3.27)
project(Glad)

add_library(glad include/glad/gles2.h src/gles2.c include/glad/egl.h src/egl.c)

target_include_directories(glad PUBLIC include/)