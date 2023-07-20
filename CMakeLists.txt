cmake_minimum_required(VERSION 3.16)
project(urchin
    VERSION 0
    DESCRIPTION "Simple Mud Experiment in C"
    HOMEPAGE_URL "https://git.warwick-new.co.uk/"
    LANGUAGES C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_CLANG_TIDY)

# Compile Shared Library
file(GLOB_RECURSE LIBRARY_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/shared_lib/*.c)

file(GLOB_RECURSE LIBRARY_HEADER_FILES
    ${CMAKE_SOURCE_DIR}/src/shared_lib/*.h)

add_library(${PROJECT_NAME} SHARED ${LIBRARY_HEADER_FILES} ${LIBRARY_SOURCE_FILES})

# Compile Server
file(GLOB_RECURSE SERVER_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/server/*.c)

file(GLOB_RECURSE SERVER_HEADER_FILES
    ${CMAKE_SOURCE_DIR}/src/server/*.h)

add_executable(${PROJECT_NAME}-server ${SERVER_HEADER_FILES} ${SERVER_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}-server ${PROJECT_NAME})

# Compile Client
file(GLOB_RECURSE CLIENT_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/client/*.c)

file(GLOB_RECURSE CLIENT_HEADER_FILES
    ${CMAKE_SOURCE_DIR}/src/client/*.h)

add_executable(${PROJECT_NAME}-client ${CLIENT_HEADER_FILES} ${CLIENT_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}-client ${PROJECT_NAME})
