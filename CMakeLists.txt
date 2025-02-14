cmake_minimum_required(VERSION 3.0)
project( Factorio )
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -O2)


add_library(OBJ OBJECT object.cpp)
target_compile_definitions(OBJ PUBLIC OBJ)

add_library(INIF OBJECT interactioninterfaces.cpp
        factory.cpp
        factory.h)
target_compile_definitions(INIF PUBLIC INIF)



add_executable( main main.cpp)

