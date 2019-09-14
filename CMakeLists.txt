cmake_minimum_required(VERSION 3.8)

project( endora )

set(CMAKE_CXX_STANDARD 17)

find_package( OpenGL )
find_package( GLEW )

file(GLOB CPP_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp src/*/*.cpp)

add_library( ${PROJECT_NAME} SHARED
        ${CPP_FILES}
)

target_link_libraries( ${PROJECT_NAME}
        PRIVATE
        OpenGL::OpenGL
        GLEW::GLEW
)

target_compile_options ( ${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic )

file(GLOB public_headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} endora/*.hpp endora/*/*.hpp single-header/endora.hpp)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")

# Make install
install(
        TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION /usr/local/lib/
        PUBLIC_HEADER DESTINATION /usr/local/include/endora
)

