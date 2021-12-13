cmake_minimum_required(VERSION 3.20)
project(SortingAlgorithms C)

set(CMAKE_C_STANDARD 99)

add_executable(SortingAlgorithms main.c SortingAlgorithms.c SortingAlgorithms.h Statistics.c Statistics.h Array.c Array.h)
