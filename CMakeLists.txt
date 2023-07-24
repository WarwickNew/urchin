cmake_minimum_required(VERSION 3.16)
project(urchin
    VERSION 0
    DESCRIPTION "Simple Mud Experiment in C"
    HOMEPAGE_URL "https://git.warwick-new.co.uk/"
    LANGUAGES C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_CLANG_TIDY)

# Get protobuf to serialize data between the server and client
# cmake config not packaged with the lib. resort to pkg config
include(FindPkgConfig)
pkg_check_modules(protobuf-c REQUIRED libprotobuf-c>=1.4.1)

# Compile Shared Library
file(GLOB_RECURSE LIBRARY_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/shared_lib/*.c)

file(GLOB_RECURSE LIBRARY_HEADER_FILES
    ${CMAKE_SOURCE_DIR}/src/shared_lib/*.h)

# Generate Protobuf code
find_program(protoc-c_EXECUTABLE NAMES protoc-c REQUIRED)
find_package_handle_standard_args(protoc-c REQUIRED_VARS protoc-c_EXECUTABLE)
file(GLOB_RECURSE PROTOBUF_PROTO_FILES
    ${CMAKE_SOURCE_DIR}/protobuf/*.proto)
add_custom_target(GenerateProtobuf)
add_custom_command(
    OUTPUT GenerateProtobuf
    DEPENDS ${protoc-c_EXECUTABLE}
    COMMAND ${protoc-c_EXECUTABLE} --c_out=${CMAKE_SOURCE_DIR}/src/protobuf_gen/ --proto_path=${CMAKE_SOURCE_DIR}/protobuf/ ${PROTOBUF_PROTO_FILES}
)

# Include protobuf generated  message formats
file(GLOB_RECURSE PROTOBUF_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/protobuf_gen/*.c)

file(GLOB_RECURSE PROTOBUF_HEADER_FILES
    ${CMAKE_SOURCE_DIR}/src/protobuf_gen/*.h)
set_source_files_properties(${PROTOBUF_HEADER_FILES} ${PROTOBUF_SOURCE_FILES} PROPERTIES GENERATED TRUE)

add_library(${PROJECT_NAME} STATIC
    GenerateProtobuf
    ${LIBRARY_HEADER_FILES}
    ${PROTOBUF_HEADER_FILES}
    ${LIBRARY_SOURCE_FILES}
    ${PROTOBUF_SOURCE_FILES}
)
add_dependencies(${PROJECT_NAME} GenerateProtobuf)

target_link_libraries(${PROJECT_NAME} PUBLIC protobuf-c)


# Compile Server
file(GLOB_RECURSE SERVER_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/server/*.c)

file(GLOB_RECURSE SERVER_HEADER_FILES
    ${CMAKE_SOURCE_DIR}/src/server/*.h)

add_executable(${PROJECT_NAME}-server ${SERVER_HEADER_FILES} ${SERVER_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}-server PUBLIC ${PROJECT_NAME})

# Compile Client
file(GLOB_RECURSE CLIENT_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/client/*.c)

file(GLOB_RECURSE CLIENT_HEADER_FILES
    ${CMAKE_SOURCE_DIR}/src/client/*.h)

add_executable(${PROJECT_NAME}-client ${CLIENT_HEADER_FILES} ${CLIENT_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}-client PUBLIC ${PROJECT_NAME})
