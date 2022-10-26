cmake_minimum_required(VERSION 3.20)
project(Fo C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "-Wall")

add_executable(Fo main.c jatek.c jatek.h megjelenites.c megjelenites.h kerdesek.csv)