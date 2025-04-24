cmake_minimum_required(VERSION 3.3)
project( Factorio  LANGUAGES CXX)
set (CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)

if (NOT DLEVEL)
    set(DLEVEL 10)
endif()

set(BUILD_SHARED_LIBS FALSE)

# SFML
# ----------------------------------------------
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    SYSTEM)
FetchContent_MakeAvailable(SFML)


# Set standarts
# ----------------------------------------------
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wpedantic -g -DDLEVEL=${DLEVEL})
include_directories(./include)

add_custom_target( build )

# got to the code stuff
include(./src/CMakeLists.txt)

# Adding directories to build
# ----------------------------------------------
add_custom_target(copy_resourses ALL)
add_custom_command(TARGET copy_resourses
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:main>/resources)
# ----------------------------------------------