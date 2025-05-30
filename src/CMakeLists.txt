set(TMP ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

message("${CMAKE_CURRENT_SOURCE_DIR}")
# Build local libraries
# ----------------------------------------------
add_library(INIF STATIC ${CMAKE_CURRENT_SOURCE_DIR}/interactioninterfaces.cpp)
target_compile_definitions(INIF PUBLIC INIF)

add_library(JSON STATIC ${CMAKE_CURRENT_SOURCE_DIR}/jsoncommunicate.cpp)
target_compile_definitions(JSON PUBLIC JSON)
target_link_libraries(JSON PUBLIC INIF SFML::Graphics)

add_library(MATERIAL STATIC ${CMAKE_CURRENT_SOURCE_DIR}/material.cpp)
target_compile_definitions(MATERIAL PUBLIC MATERIAL)
target_link_libraries(MATERIAL PUBLIC INIF)

add_library(OBJ STATIC ${CMAKE_CURRENT_SOURCE_DIR}/object.cpp)
target_compile_definitions(OBJ PUBLIC OBJ)
target_link_libraries(OBJ PUBLIC JSON INIF)

add_library(BUILDING STATIC ${CMAKE_CURRENT_SOURCE_DIR}/building.cpp)
target_compile_definitions(BUILDING PUBLIC BUILDING)
target_link_libraries(BUILDING PUBLIC OBJ INIF MATERIAL JSON)

add_library(FACTORY STATIC ${CMAKE_CURRENT_SOURCE_DIR}/factory.cpp)
target_compile_definitions(FACTORY PUBLIC FACTORY)
target_link_libraries(FACTORY PUBLIC OBJ INIF MATERIAL BUILDING JSON)

add_library(INSERTER STATIC ${CMAKE_CURRENT_SOURCE_DIR}/inserter.cpp)
target_compile_definitions(INSERTER PUBLIC INSERTER)
target_link_libraries(INSERTER PUBLIC OBJ INIF MATERIAL BUILDING JSON)

add_library(CONVEYER STATIC ${CMAKE_CURRENT_SOURCE_DIR}/conveyer.cpp)
target_compile_definitions(CONVEYER PUBLIC CONVEYER)
target_link_libraries(CONVEYER PUBLIC OBJ INIF MATERIAL BUILDING JSON)

add_library(SESLOGIC STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sessionlogic.cpp)
target_compile_definitions(SESLOGIC PUBLIC SESLOGIC)
target_link_libraries(SESLOGIC PUBLIC CONVEYER INSERTER FACTORY OBJ INIF MATERIAL BUILDING JSON)


add_executable( test ${CMAKE_CURRENT_SOURCE_DIR}/testl.cpp)
target_link_libraries(test SESLOGIC)

add_executable( test2 ${CMAKE_CURRENT_SOURCE_DIR}/testld.cpp)
target_link_libraries(test2 SESLOGIC)

add_library(WINDOW STATIC ${CMAKE_CURRENT_SOURCE_DIR}/window.cpp)
target_compile_definitions(WINDOW PUBLIC WINDOW)
target_link_libraries(WINDOW PUBLIC SESLOGIC SFML::Audio SFML::Graphics SFML::System SFML::Window)

# main
# ----------------------------------------------
add_executable( SIBIRIO ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(SIBIRIO WINDOW)
# ----------------------------------------------

set(CMAKE_CURRENT_SOURCE_DIR  ${TMP})

