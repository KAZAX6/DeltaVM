cmake_minimum_required(VERSION 3.16)
project(DeltaScript C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O3 -fno-strict-aliasing -g")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
include_directories(include)
file(GLOB_RECURSE SRC
    src/*.c
)
add_library(delta_vm SHARED ${SRC})
set_target_properties(delta_vm PROPERTIES
    OUTPUT_NAME "DeltaVM"
)
set_target_properties(delta_vm PROPERTIES
    VERSION 1.5.0
    SOVERSION 1
)