cmake_minimum_required(VERSION 3.16)
project(urchin
    VERSION 0
    DESCRIPTION "Simple Mud Experiment in C"
    HOMEPAGE_URL "https://git.warwick-new.co.uk/"
    LANGUAGES C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_CLANG_TIDY)

include(CheckIncludeFile)
add_subdirectory(${CMAKE_SOURCE_DIR}/urchin-util)

# Compile Server
file(GLOB_RECURSE SERVER_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/server/*.c)

file(GLOB_RECURSE SERVER_HEADER_FILES
    ${CMAKE_SOURCE_DIR}/src/server/*.h)

add_executable(${PROJECT_NAME}-server ${SERVER_HEADER_FILES} ${SERVER_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}-server PUBLIC urchin-util)

# Compile Client
file(GLOB_RECURSE CLIENT_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/client/*.c)

file(GLOB_RECURSE CLIENT_HEADER_FILES
    ${CMAKE_SOURCE_DIR}/src/client/*.h)

add_executable(${PROJECT_NAME}-client ${CLIENT_HEADER_FILES} ${CLIENT_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}-client PUBLIC urchin-util)
