cmake_minimum_required(VERSION 3.14)
project(correctionbanqueinteractive)

set(CMAKE_CXX_STANDARD 14)

add_executable(correctionbanqueinteractive main.cpp Compte.cpp Compte.h Client.cpp Client.h Banque.cpp Banque.h utils.cpp utils.h)