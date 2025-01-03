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

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <memory>
#include <cstdint>
#include <string_view>

inline constexpr std::string_view APP_TITLE = "OpenGL Window";

inline constexpr std::uint16_t WINDOW_WIDTH = 800;
inline constexpr std::uint16_t WINDOW_HEIGHT = 600;

class App
{
public:
    App() = default;
    ~App();

    bool Init();
    void Run();
    void Render();

    inline bool IsRunning() const
    {
        return !glfwWindowShouldClose(window);
    }

private:
    GLFWwindow* window;
};