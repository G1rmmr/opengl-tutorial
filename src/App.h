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

#include <string_view>
#include <memory>
#include <random>

#include "Shader.h"
#include "Camera.h"
#include "Manager.h"

#include "Cube.h"
#include "Map.h"

inline constexpr std::string_view APP_TITLE = "OpenGL Window";

inline constexpr GLushort WINDOW_WIDTH = 800;
inline constexpr GLushort WINDOW_HEIGHT = 600;

class App
{
public:
    App();
    ~App();

    GLboolean Init();
    void Run();

    inline GLboolean IsRunning() const
    {
        return !glfwWindowShouldClose(window);
    }

private:
    const GLfloat target_frame_time = 0.0333f;

    glm::vec3 _color = glm::vec3(1.f, 1.f, 0.8f);

    std::unique_ptr<Manager> manager;
    std::unique_ptr<Shader> lighting_shader;
    std::unique_ptr<Shader> post_shader;
    std::unique_ptr<Camera> cam;

    GLFWwindow* window;

    GLfloat last_x;
    GLfloat last_y;

    GLfloat yaw;
    GLfloat pitch;

    GLfloat dt;
    GLfloat last_frame;

    GLuint fbo;
    GLuint color_text;
    GLuint rbo;

    GLuint q_vao;
    GLuint q_vbo;

    GLboolean first_mouse;
    GLboolean change_light = false;

    void Render();

    void ProcessInput(GLFWwindow* window);
    void MouseCallback(GLFWwindow* window, GLdouble x, GLdouble y);

    inline static void CursorPosCallback(GLFWwindow* window, GLdouble x, GLdouble y)
    {
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
        if(app) app->MouseCallback(window, x, y);
    }

    inline static void FramebufSizeCallback(GLFWwindow* window, GLint w, GLint h)
    {
        glViewport(0, 0, w, h);
    }

    inline void GenerateRandomColor()
    {
        std::mt19937 rng{std::random_device{}()};

        std::uniform_real_distribution<GLfloat> _x{0.f, 1.f};
        std::uniform_real_distribution<GLfloat> _y{0.f, 1.f};
        std::uniform_real_distribution<GLfloat> _z{0.f, 1.f};

        _color = glm::vec3(_x(rng), _y(rng), _z(rng));
    }
};