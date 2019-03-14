cmake_minimum_required(VERSION 3.8)

project( endora )

set(CMAKE_CXX_STANDARD 17)

find_package( OpenGL )
find_package( GLEW )

file(GLOB HPP_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/endora/*.hpp include/endora/*/*.hpp)
file(GLOB CPP_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp src/*/*.cpp)


add_library(
        ${PROJECT_NAME}
        SHARED
        ${CPP_FILES}
        ${HPP_FILES}
)

target_link_libraries( ${PROJECT_NAME}
        PRIVATE
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
)

target_include_directories( ${PROJECT_NAME}
        SYSTEM BEFORE PRIVATE include
)

target_compile_options ( ${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic )


get_directory_property(has_parent PARENT_DIRECTORY)
if (has_parent)
    set ( PUBLISHED_FILES include/${PROJECT_NAME} PARENT_SCOPE )
endif()

# Make install
install(
        TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION /usr/local/lib/
)

install(
        DIRECTORY include/endora/
        DESTINATION /usr/local/include/endora

        PATTERN "include/endora/*"
)
