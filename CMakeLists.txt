cmake_minimum_required(VERSION 3.5)
project( Factorio )
set(CMAKE_CXX_STANDARD 17)

if (NOT DLEVEL)
    set(DLEVEL 10)
endif()

add_compile_options(-Wall -Wextra -Wpedantic -g -DDLEVEL=${DLEVEL})
include_directories(./include)

# SFML
# ----------------------------------------------
# It works on MacOs, don't break it!
if (APPLE)
    set(SFML_DIR "/opt/homebrew/Cellar/sfml/3.0.0_1/lib/cmake/SFML")
endif (APPLE)

find_package(SFML 3.0 REQUIRED COMPONENTS Graphics Audio)
# ----------------------------------------------

# Linking local libraries
# ----------------------------------------------
add_library(INIF STATIC interactioninterfaces.cpp)
target_compile_definitions(INIF PUBLIC INIF)

add_library(JSON STATIC jsoncommunicate.cpp)
target_compile_definitions(JSON PUBLIC JSON)
target_link_libraries(JSON PUBLIC INIF)

# ////
add_library(WINDOW STATIC window.cpp)
target_compile_definitions(WINDOW PUBLIC WINDOW)
target_link_libraries(WINDOW PUBLIC Graphics)
# ////

add_library(MATERIAL STATIC material.cpp)
target_compile_definitions(MATERIAL PUBLIC MATERIAL)
target_link_libraries(MATERIAL PUBLIC INIF)

add_library(OBJ STATIC object.cpp)
target_compile_definitions(OBJ PUBLIC OBJ)
target_link_libraries(OBJ PUBLIC JSON INIF)

add_library(BUILDING STATIC building.cpp)
target_compile_definitions(BUILDING PUBLIC BUILDING)
target_link_libraries(BUILDING PUBLIC OBJ INIF MATERIAL JSON)

add_library(FACTORY STATIC factory.cpp)
target_compile_definitions(FACTORY PUBLIC FACTORY)
target_link_libraries(FACTORY PUBLIC OBJ INIF MATERIAL BUILDING JSON)


add_executable( main main.cpp)
# ----------------------------------------------


# Linking
# ----------------------------------------------
target_link_libraries(
        main
        JSON MATERIAL FACTORY BUILDING WINDOW
        SFML::Graphics SFML::Audio
)
# ----------------------------------------------


# Adding directories to build
# ----------------------------------------------
add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:main>/resources)
# ----------------------------------------------