cmake_minimum_required(VERSION 3.2)

project(fivePhilosophers VERSION 1.0 LANGUAGES CXX)

add_executable(fivePhilosophers 
    Multithreading.cpp
    Philosopher.hpp
    Server.cpp
    Server.hpp
    )