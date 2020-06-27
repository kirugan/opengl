cmake_minimum_required(VERSION 3.15)
project(myapp)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory("deps/glfw-3.3.2")
add_subdirectory("deps/glew-2.1.0/build/cmake")

include_directories("deps/glew-2.1.0/include")

add_executable(myapp "main.cpp")
target_link_libraries(myapp glfw glew_s ${OPENGL_LIBRARY})