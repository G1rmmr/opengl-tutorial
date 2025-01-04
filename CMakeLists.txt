cmake_minimum_required(VERSION 3.10)
project(opengl)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    src/main.cpp
    src/App.cpp
    src/Shader.cpp
    src/glad.c
    src/Camera.cpp
)

add_definitions(-DGL_SILENCE_DEPRECATION)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(opengl ${SOURCES})

target_include_directories(opengl PRIVATE
    ${OPENGL_INCLUDE_DIRS}
    /usr/local/include
    /usr/local/include/glfw
    /usr/local/include/glm
)

target_link_libraries(opengl ${OPENGL_LIBRARIES} glfw)