// Created on Fri Jan 03 2025
// © 2025 BLACKHAND Studio. All rights reserved.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//      http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "glad.h"

#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Camera.h"

#include <cstdint>
#include <string_view>

inline constexpr std::string_view APP_TITLE = "OpenGL Window";

inline constexpr std::uint16_t WINDOW_WIDTH = 800;
inline constexpr std::uint16_t WINDOW_HEIGHT = 600;

class App
{
public:
    App();
    ~App();

    bool Init();
    void Run();

    inline bool IsRunning() const
    {
        return !glfwWindowShouldClose(window);
    }

private:
    GLFWwindow* window;
    Shader* shader;

    Camera cam;

    float last_x;
    float last_y;

    float yaw;
    float pitch;

    float dt;
    float last_frame;

    unsigned int vao;
    unsigned int vbo;

    bool first_mouse;

    void Render();

    void ProcessInput(GLFWwindow* window);
    void MouseCallback(GLFWwindow* window, double x, double y);

    inline static void CursorPosCallback(GLFWwindow* window, double x, double y)
    {
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
        if(app) app->MouseCallback(window, x, y);
    }

    inline static void FramebufSizeCallback(GLFWwindow* window, int w, int h)
    {
        glViewport(0, 0, w, h);
    }
};