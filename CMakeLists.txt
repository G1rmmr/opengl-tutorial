cmake_minimum_required(VERSION 3.10)
project(opengl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

# Suppress deprecation warnings for macOS
add_definitions(-DGL_SILENCE_DEPRECATION)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Platform-specific settings
if(WIN32)
    # Use vcpkg paths for GLFW on Windows
    set(CMAKE_PREFIX_PATH "C:/vcpkg/installed/x64-windows/share")
    find_package(glfw3 REQUIRED CONFIG)
    set(GLFW3_INCLUDE_DIRS "C:/vcpkg/installed/x64-windows/include")
elseif(UNIX)
    # Use system-installed GLFW on Linux
    find_package(glfw3 REQUIRED)
    set(GLFW3_INCLUDE_DIRS "/usr/local/include")
endif()

# Add executable
add_executable(opengl ${SOURCES})

# Include directories
target_include_directories(opengl PRIVATE
    ${OPENGL_INCLUDE_DIRS}
    ${GLFW3_INCLUDE_DIRS}
    /usr/local/include/glm  # Assuming GLM is installed here
)

# Link libraries
target_link_libraries(opengl PRIVATE ${OPENGL_LIBRARIES} glfw)
