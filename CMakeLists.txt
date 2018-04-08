cmake_minimum_required(VERSION 3.5)
set(LIB_NAME endora)

project(${LIB_NAME})

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -Wextra)

find_package( OpenGL )
find_package( GLEW )


file(GLOB_RECURSE HPP_FILES include/*.hpp)
file(GLOB_RECURSE CPP_FILES src/*.cpp)


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
        PRIVATE include
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
