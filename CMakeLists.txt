cmake_minimum_required(VERSION 3.29)
project(caesar_cipher_utility C)

set(CMAKE_C_STANDARD 99)

add_executable(caesar_cipher_utility main.c
        caesar.c
        caesar.h
        io_functions.c
        io_functions.h)


add_executable(run_tests run_tests.c caesar.c io_functions.c)
