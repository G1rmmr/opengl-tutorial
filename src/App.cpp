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

// 각 정점 당: (position.x, position.y, position.z, normal.x, normal.y, normal.z, color.r, color.g, color.b)
std::vector<GLfloat> snow_vertices = {
    // Front face (z = -0.5, normal = ( 0,  0, -1 ))
    -0.5f, -0.5f, -0.5f,   0.f,  0.f, -1.f,   1.f, 1.f, 1.f,
     0.5f, -0.5f, -0.5f,   0.f,  0.f, -1.f,   1.f, 1.f, 1.f,
     0.5f,  0.5f, -0.5f,   0.f,  0.f, -1.f,   1.f, 1.f, 1.f,
    -0.5f,  0.5f, -0.5f,   0.f,  0.f, -1.f,   1.f, 1.f, 1.f,

    // Back face (z = 0.5, normal = ( 0,  0,  1 ))
    -0.5f, -0.5f,  0.5f,   0.f,  0.f,  1.f,   1.f, 1.f, 1.f,
     0.5f, -0.5f,  0.5f,   0.f,  0.f,  1.f,   1.f, 1.f, 1.f,
     0.5f,  0.5f,  0.5f,   0.f,  0.f,  1.f,   1.f, 1.f, 1.f,
    -0.5f,  0.5f,  0.5f,   0.f,  0.f,  1.f,   1.f, 1.f, 1.f,

    // Left face (x = -0.5, normal = (-1, 0, 0))
    -0.5f, -0.5f, -0.5f,  -1.f,  0.f,  0.f,   1.f, 1.f, 1.f,
    -0.5f, -0.5f,  0.5f,  -1.f,  0.f,  0.f,   1.f, 1.f, 1.f,
    -0.5f,  0.5f,  0.5f,  -1.f,  0.f,  0.f,   1.f, 1.f, 1.f,
    -0.5f,  0.5f, -0.5f,  -1.f,  0.f,  0.f,   1.f, 1.f, 1.f,

    // Right face (x = 0.5, normal = ( 1, 0, 0))
     0.5f, -0.5f, -0.5f,   1.f,  0.f,  0.f,   1.f, 1.f, 1.f,
     0.5f, -0.5f,  0.5f,   1.f,  0.f,  0.f,   1.f, 1.f, 1.f,
     0.5f,  0.5f,  0.5f,   1.f,  0.f,  0.f,   1.f, 1.f, 1.f,
     0.5f,  0.5f, -0.5f,   1.f,  0.f,  0.f,   1.f, 1.f, 1.f,

    // Top face (y = 0.5, normal = ( 0, 1, 0))
    -0.5f,  0.5f, -0.5f,   0.f,  1.f,  0.f,   1.f, 1.f, 1.f,
     0.5f,  0.5f, -0.5f,   0.f,  1.f,  0.f,   1.f, 1.f, 1.f,
     0.5f,  0.5f,  0.5f,   0.f,  1.f,  0.f,   1.f, 1.f, 1.f,
    -0.5f,  0.5f,  0.5f,   0.f,  1.f,  0.f,   1.f, 1.f, 1.f,

    // Bottom face (y = -0.5, normal = (0, -1, 0))
    -0.5f, -0.5f, -0.5f,   0.f, -1.f,  0.f,   1.f, 1.f, 1.f,
     0.5f, -0.5f, -0.5f,   0.f, -1.f,  0.f,   1.f, 1.f, 1.f,
     0.5f, -0.5f,  0.5f,   0.f, -1.f,  0.f,   1.f, 1.f, 1.f,
    -0.5f, -0.5f,  0.5f,   0.f, -1.f,  0.f,   1.f, 1.f, 1.f
};

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

GLboolean App::Init()
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

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

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

    GLint width;
    GLint height;

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    shader = std::make_unique<Shader>("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    manager = std::make_unique<Manager>();

    auto map = std::make_shared<Map>();
    manager->SetRoot(map);

    RandomCubeFactory factory(5.f, 100.f, 100.f, 10.f, 500);
    factory.GenerateCubes(*manager, shader->id, snow_vertices);

    std::vector<GLfloat> ground_vertices = {
        // ----- Front face (z = -1, normal = ( 0,  0, -1 )) -----
        -1.f, -0.5f, -1.f,   0.f,  0.f, -1.f,   0.7f, 0.7f, 0.7f,
        1.f, -0.5f, -1.f,   0.f,  0.f, -1.f,   0.7f, 0.7f, 0.7f,
        1.f,  0.5f, -1.f,   0.f,  0.f, -1.f,   0.7f, 0.7f, 0.7f,
        -1.f,  0.5f, -1.f,   0.f,  0.f, -1.f,   0.7f, 0.7f, 0.7f,

        // ----- Back face (z =  1, normal = ( 0,  0,  1 )) -----
        -1.f, -0.5f,  1.f,   0.f,  0.f,  1.f,   0.7f, 0.7f, 0.7f,
        1.f, -0.5f,  1.f,   0.f,  0.f,  1.f,   0.7f, 0.7f, 0.7f,
        1.f,  0.5f,  1.f,   0.f,  0.f,  1.f,   0.7f, 0.7f, 0.7f,
        -1.f,  0.5f,  1.f,   0.f,  0.f,  1.f,   0.7f, 0.7f, 0.7f,

        // ----- Left face (x = -1, normal = (-1, 0, 0)) -----
        -1.f, -0.5f, -1.f,  -1.f,  0.f,  0.f,   0.7f, 0.7f, 0.7f,
        -1.f, -0.5f,  1.f,  -1.f,  0.f,  0.f,   0.7f, 0.7f, 0.7f,
        -1.f,  0.5f,  1.f,  -1.f,  0.f,  0.f,   0.7f, 0.7f, 0.7f,
        -1.f,  0.5f, -1.f,  -1.f,  0.f,  0.f,   0.7f, 0.7f, 0.7f,

        // ----- Right face (x =  1, normal = ( 1, 0, 0)) -----
        1.f, -0.5f, -1.f,   1.f,  0.f,  0.f,   0.7f, 0.7f, 0.7f,
        1.f, -0.5f,  1.f,   1.f,  0.f,  0.f,   0.7f, 0.7f, 0.7f,
        1.f,  0.5f,  1.f,   1.f,  0.f,  0.f,   0.7f, 0.7f, 0.7f,
        1.f,  0.5f, -1.f,   1.f,  0.f,  0.f,   0.7f, 0.7f, 0.7f,

        // ----- Top face (y =  0.5, normal = (0, 1, 0)) -----
        -1.f,  0.5f, -1.f,   0.f,  1.f,  0.f,   0.3f, 0.3f, 0.3f,
        1.f,  0.5f, -1.f,   0.f,  1.f,  0.f,   0.3f, 0.3f, 0.3f,
        1.f,  0.5f,  1.f,   0.f,  1.f,  0.f,   0.3f, 0.3f, 0.3f,
        -1.f,  0.5f,  1.f,   0.f,  1.f,  0.f,   0.3f, 0.3f, 0.3f,

        // ----- Bottom face (y = -0.5, normal = (0, -1, 0)) -----
        -1.f, -0.5f, -1.f,   0.f, -1.f,  0.f,   0.7f, 0.7f, 0.7f,
        1.f, -0.5f, -1.f,   0.f, -1.f,  0.f,   0.7f, 0.7f, 0.7f,
        1.f, -0.5f,  1.f,   0.f, -1.f,  0.f,   0.7f, 0.7f, 0.7f,
        -1.f, -0.5f,  1.f,   0.f, -1.f,  0.f,   0.7f, 0.7f, 0.7f
    };


    auto ground = std::make_shared<Cube>(
        glm::vec3(0.f, -1.f, 0.f),
        glm::quat(0.f, 0.f, 0.f, 0.f),
        glm::vec3(100.f, 1.f, 100.f),
        shader->id,
        ground_vertices
    );

    std::vector<GLfloat> moon_vertices = {
        // Front face (z = -0.5, normal = ( 0,  0, -1 ))
    -0.5f, -0.5f, -0.5f,   0.f,  0.f, -1.f,   1.f, 1.f, 0.8f,
     0.5f, -0.5f, -0.5f,   0.f,  0.f, -1.f,   1.f, 1.f, 0.8f,
     0.5f,  0.5f, -0.5f,   0.f,  0.f, -1.f,   1.f, 1.f, 0.8f,
    -0.5f,  0.5f, -0.5f,   0.f,  0.f, -1.f,   1.f, 1.f, 0.8f,

    // Back face (z = 0.5, normal = ( 0,  0,  1 ))
    -0.5f, -0.5f,  0.5f,   0.f,  0.f,  1.f,   1.f, 1.f, 0.8f,
     0.5f, -0.5f,  0.5f,   0.f,  0.f,  1.f,   1.f, 1.f, 0.8f,
     0.5f,  0.5f,  0.5f,   0.f,  0.f,  1.f,   1.f, 1.f, 0.8f,
    -0.5f,  0.5f,  0.5f,   0.f,  0.f,  1.f,   1.f, 1.f, 0.8f,

    // Left face (x = -0.5, normal = (-1, 0, 0))
    -0.5f, -0.5f, -0.5f,  -1.f,  0.f,  0.f,   1.f, 1.f, 0.8f,
    -0.5f, -0.5f,  0.5f,  -1.f,  0.f,  0.f,   1.f, 1.f, 0.8f,
    -0.5f,  0.5f,  0.5f,  -1.f,  0.f,  0.f,   1.f, 1.f, 0.8f,
    -0.5f,  0.5f, -0.5f,  -1.f,  0.f,  0.f,   1.f, 1.f, 0.8f,

    // Right face (x = 0.5, normal = ( 1, 0, 0))
     0.5f, -0.5f, -0.5f,   1.f,  0.f,  0.f,   1.f, 1.f, 0.8f,
     0.5f, -0.5f,  0.5f,   1.f,  0.f,  0.f,   1.f, 1.f, 0.8f,
     0.5f,  0.5f,  0.5f,   1.f,  0.f,  0.f,   1.f, 1.f, 0.8f,
     0.5f,  0.5f, -0.5f,   1.f,  0.f,  0.f,   1.f, 1.f, 0.8f,

    // Top face (y = 0.5, normal = ( 0, 1, 0))
    -0.5f,  0.5f, -0.5f,   0.f,  1.f,  0.f,   1.f, 1.f, 0.8f,
     0.5f,  0.5f, -0.5f,   0.f,  1.f,  0.f,   1.f, 1.f, 0.8f,
     0.5f,  0.5f,  0.5f,   0.f,  1.f,  0.f,   1.f, 1.f, 0.8f,
    -0.5f,  0.5f,  0.5f,   0.f,  1.f,  0.f,   1.f, 1.f, 0.8f,

    // Bottom face (y = -0.5, normal = (0, -1, 0))
    -0.5f, -0.5f, -0.5f,   0.f, -1.f,  0.f,   1.f, 1.f, 0.8f,
     0.5f, -0.5f, -0.5f,   0.f, -1.f,  0.f,   1.f, 1.f, 0.8f,
     0.5f, -0.5f,  0.5f,   0.f, -1.f,  0.f,   1.f, 1.f, 0.8f,
    -0.5f, -0.5f,  0.5f,   0.f, -1.f,  0.f,   1.f, 1.f, 0.8f
    };

    auto moon = std::make_shared<Cube>(
        glm::vec3(0.f, 3.f, 3.f),
        glm::quat(0.f, 0.f, 0.f, 0.f),
        glm::vec3(10.f, 10.f, 10.f),
        shader->id,
        moon_vertices
    );

    manager->AddChild(std::make_unique<Scene>(ground));
    manager->AddChild(std::make_unique<Scene>(moon));

    cam = std::make_unique<Camera>();
    return true;
}

void App::Run()
{
    GLfloat curr_frame = static_cast<GLfloat>(glfwGetTime());
    dt = curr_frame - last_frame;
    last_frame = curr_frame;

    ProcessInput(window);
    manager->Update(dt);
    Render();
    glfwPollEvents();
}

void App::Render()
{
    glClearColor(0.0f, 0.0f, 0.2f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->Use();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = cam->GetViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(cam->zoom),
        static_cast<GLfloat>(WINDOW_WIDTH) / static_cast<GLfloat>(WINDOW_HEIGHT),
        0.1f, 100.0f);

    shader->SetMat("proj", proj);
    shader->SetMat("view", view);
    shader->SetMat("model", model);

    shader->SetVec("light_pos", glm::vec3(0.f, 10.f, 0.f));
    shader->SetVec("view_pos", cam->pos);
    shader->SetVec("light_color", glm::vec3(1.f, 1.f, 1.f));

    manager->Draw(view, proj);
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

void App::MouseCallback(GLFWwindow* window, GLdouble x, GLdouble y)
{
    if(first_mouse)
    {
        last_x = static_cast<GLfloat>(x);
        last_y = static_cast<GLfloat>(y);
        first_mouse = false;
    }

    GLfloat off_x = static_cast<GLfloat>(x) - last_x;
    GLfloat off_y = last_y - static_cast<GLfloat>(y);

    last_x = static_cast<GLfloat>(x);
    last_y = static_cast<GLfloat>(y);

    cam->ProcessMouseMovement(off_x, off_y);
}