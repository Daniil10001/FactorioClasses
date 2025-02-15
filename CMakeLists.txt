cmake_minimum_required(VERSION 3.0)
project( Factorio )
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -O2)


add_library(INIF STATIC interactioninterfaces.cpp)
target_compile_definitions(INIF PUBLIC INIF)

add_library(JSON STATIC interactioninterfaces.cpp)
target_compile_definitions(JSON PUBLIC JSON)

add_library(OBJ STATIC object.cpp)
target_compile_definitions(OBJ PUBLIC OBJ)
target_link_libraries(OBJ PUBLIC JSON)

add_library(MATERIAL STATIC material.cpp)
target_compile_definitions(MATERIAL PUBLIC MATERIAL)
target_link_libraries(MATERIAL PUBLIC INIF)

add_library(BUILDING STATIC building.cpp)
target_compile_definitions(BUILDING PUBLIC BUILDING)
target_link_libraries(BUILDING PUBLIC OBJ INIF MATERIAL JSON)

add_library(FACTORY STATIC factory.cpp)
target_compile_definitions(MATERIAL PUBLIC MATERIAL)
target_link_libraries(FACTORY PUBLIC OBJ INIF MATERIAL BUILDING JSON)


add_executable( main main.cpp)

