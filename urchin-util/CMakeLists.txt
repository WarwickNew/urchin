cmake_minimum_required(VERSION 3.16)
project(urchin-util
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
file(GLOB LIBRARY_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

file(GLOB LIBRARY_HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

# Generate Protobuf code
find_program(protoc-c_EXECUTABLE NAMES protoc-c REQUIRED)
find_package_handle_standard_args(protoc-c REQUIRED_VARS protoc-c_EXECUTABLE)
file(GLOB_RECURSE PROTOBUF_PROTO_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/*.proto)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/protobuf_gen/)
add_custom_target(GenerateProtobuf)
execute_process( # Execute process is used to generate this code before the initial file glob
    COMMAND ${protoc-c_EXECUTABLE} --c_out=${CMAKE_CURRENT_SOURCE_DIR}/src/protobuf_gen/ --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/protobuf/ ${PROTOBUF_PROTO_FILES}
)
add_custom_command( # add_custom command is used to update the generated code after .proto files have been modified
    OUTPUT GenerateProtobuf
    DEPENDS ${protoc-c_EXECUTABLE}
    COMMAND ${protoc-c_EXECUTABLE} --c_out=${CMAKE_CURRENT_SOURCE_DIR}/src/protobuf_gen/ --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/protobuf/ ${PROTOBUF_PROTO_FILES}
)

# Include protobuf generated  message formats
file(GLOB_RECURSE PROTOBUF_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/protobuf_gen/*.c)

file(GLOB_RECURSE PROTOBUF_HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/protobuf_gen/*.h)
set_source_files_properties(${PROTOBUF_HEADER_FILES} ${PROTOBUF_SOURCE_FILES} PROPERTIES GENERATED TRUE)

add_library(${PROJECT_NAME} SHARED
    GenerateProtobuf
    ${LIBRARY_HEADER_FILES}
    ${PROTOBUF_HEADER_FILES}
    ${LIBRARY_SOURCE_FILES}
    ${PROTOBUF_SOURCE_FILES}
)
target_link_libraries(${PROJECT_NAME} PUBLIC protobuf-c)
target_include_directories(${PROJECT_NAME} PUBLIC include)

install(
	TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
