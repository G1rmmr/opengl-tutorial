cmake_minimum_required(VERSION 3.10)
project(opengl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c")

add_definitions(-DGL_SILENCE_DEPRECATION)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

if(WIN32)
    find_package(glfw3 REQUIRED PATHS "C:/vcpkg/installed/x64-windows/share/glfw3" NO_DEFAULT_PATH)
    set(GLFW3_LIB glfw)
    set(GLFW3_INCLUDE_DIRS "C:/vcpkg/installed/x64-windows/include")
elseif(UNIX)
    find_package(glfw3 REQUIRED)
    set(GLFW3_LIB glfw)
    set(GLFW3_INCLUDE_DIRS "/usr/local/include")
endif()

add_executable(opengl ${SOURCES})

target_include_directories(opengl PRIVATE
    ${OPENGL_INCLUDE_DIRS}
    ${GLFW3_INCLUDE_DIRS}
    /usr/local/include/glm
)

target_link_libraries(opengl PRIVATE ${OPENGL_LIBRARIES} ${GLFW3_LIB})