cmake_minimum_required(VERSION 3.10)

project(suffix_array_accelerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(app_suffix_array
    apps/app_main.cpp
    src/suffix_array.cpp
)
