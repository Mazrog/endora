cmake_minimum_required(VERSION 3.5)
set(LIB_NAME endora)

project(${LIB_NAME})

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -Wextra)

find_package( OpenGL )
find_package( GLEW )

message(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB HPP_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/*.hpp include/*/*.hpp include/*/*.tpp)
file(GLOB CPP_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp src/*/*.cpp)


add_library(
        ${LIB_NAME}
        SHARED
        ${CPP_FILES}
)

target_link_libraries( ${LIB_NAME}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        IL
)

target_include_directories( ${LIB_NAME}
        SYSTEM BEFORE PRIVATE include
)

# Make install
install(
        TARGETS ${LIB_NAME}
        LIBRARY DESTINATION /usr/local/lib/
)

install(
        DIRECTORY include/
        DESTINATION /usr/local/include/endora

        PATTERN "include/*"
)
