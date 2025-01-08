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

#include "App.h"

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

App::App() 
    : window(nullptr), shader(nullptr), cam(),
    last_x(WINDOW_WIDTH * 0.5f), last_y(WINDOW_HEIGHT * 0.5f),
    first_mouse(true), dt(0.0f), last_frame(0.0f)
{

}

App::~App()
{
    glfwTerminate();
}

bool App::Init()
{
    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return false;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        APP_TITLE.data(),
        nullptr,
        nullptr);

    if(!window)
    {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, CursorPosCallback);
    glfwSetFramebufferSizeCallback(window, FramebufSizeCallback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "GLAD INIT FAILED\n");
        return false;
    }

    const GLubyte* version = glGetString(GL_VERSION);
    printf("OpenGL version : %s\n", version);

    const GLubyte* renderer = glGetString(GL_RENDERER);
    printf("Renderer : %s\n", renderer);

    GLint width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    shader = std::make_unique<Shader>("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    auto cube = std::make_shared<Cube>(
        glm::vec3(0.f, 0.f, 0.f),
        glm::quat(1.f, 0.f, 0.f, 0.f),
        glm::vec3(1.f, 1.f, 1.f)
    );

    manager = std::make_unique<Manager>();
    manager->SetRoot(cube);

    cam = std::make_unique<Camera>();
    return true;
}

void App::Run()
{
    while(!glfwWindowShouldClose(window))
    {
        float curr_frame = static_cast<float>(glfwGetTime());
        dt = curr_frame - last_frame;
        last_frame = curr_frame;

        ProcessInput(window);
        Render();
        glfwPollEvents();
    }
}

void App::Render()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->Use();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = cam->GetViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(cam->zoom), 
        (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

    shader->SetMat("proj", proj);
    shader->SetMat("view", view);
    shader->SetMat("model", model);

    shader->SetVec("light_pos", glm::vec3(1.2f, 1.0f, 2.0f));
    shader->SetVec("view_pos", cam->pos);
    shader->SetVec("light_color", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->SetVec("object_color", glm::vec3(1.0f, 0.5f, 0.31f));

    manager->Draw(shader->id, view, proj);
    glfwSwapBuffers(window);
}

void App::ProcessInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam->ProcessKeyboard(Camera::Movement::Forward, dt);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam->ProcessKeyboard(Camera::Movement::Backward, dt);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam->ProcessKeyboard(Camera::Movement::Left, dt);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam->ProcessKeyboard(Camera::Movement::Right, dt);
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void App::MouseCallback(GLFWwindow* window, double x, double y)
{
    if(first_mouse)
    {
        last_x = static_cast<float>(x);
        last_y = static_cast<float>(y);
        first_mouse = false;
    }

    float off_x = static_cast<float>(x) - last_x;
    float off_y = last_y - static_cast<float>(y);

    last_x = static_cast<float>(x);
    last_y = static_cast<float>(y);

    cam->ProcessMouseMovement(off_x, off_y);
}