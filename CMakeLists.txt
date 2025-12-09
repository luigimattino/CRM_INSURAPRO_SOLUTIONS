cmake_minimum_required(VERSION 4.0)
project(CRM_INSURAPRO_SOLUTIONS)

set(CMAKE_CXX_STANDARD 20)

add_executable(CRM_INSURAPRO_SOLUTIONS main.cpp
        csv_utils.h
        Cliente.h
        Cliente.cpp
        Interazione.h
        Interazione.cpp)
