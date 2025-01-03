cmake_minimum_required(VERSION 3.10)
project(opengl)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    /usr/local/include
    /usr/local/include/glfw
    /usr/local/include/glm
)

add_executable(opengl src/main.cpp)

target_link_libraries(opengl ${OPENGL_LIBRARIES} glfw)
