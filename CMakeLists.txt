cmake_minimum_required(VERSION 3.10)
project(opengl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c")

add_definitions(-DGL_SILENCE_DEPRECATION)

if(WIN32)
    set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-windows")
elseif(UNIX)
    set(CMAKE_PREFIX_PATH "/usr/local/lib/cmake/glfw3")
endif()

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(opengl ${SOURCES})

target_include_directories(opengl PRIVATE
    ${OPENGL_INCLUDE_DIRS}
    ${GLFW3_INCLUDE_DIRS}
    /usr/local/include/glm
)

target_link_libraries(opengl PRIVATE ${OPENGL_LIBRARIES} ${GLFW3_LIB})
