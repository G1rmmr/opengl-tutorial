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

#include <random>

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
    : window(nullptr), lighting_shader(nullptr), post_shader(nullptr), cam(nullptr),
    last_x(WINDOW_WIDTH * 0.5f), last_y(WINDOW_HEIGHT * 0.5f), first_mouse(true)
{

}

App::~App()
{
    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &color_text);
    glDeleteRenderbuffers(1, &rbo);
    glDeleteVertexArrays(1, &q_vao);
    glDeleteBuffers(1, &q_vbo);
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
        monitor,
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

    lighting_shader = std::make_unique<Shader>("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    post_shader = std::make_unique<Shader>("../shaders/post_processing.vert", "../shaders/post_processing.frag");

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &color_text);
    glBindTexture(GL_TEXTURE_2D, color_text);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_text, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WINDOW_WIDTH, WINDOW_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        fprintf(stderr, "Framebuffer not complete!\n");
        
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    GLfloat quads[] = {
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
    };

    glGenVertexArrays(1, &q_vao);
    glGenBuffers(1, &q_vbo);

    glBindVertexArray(q_vao);

    glBindBuffer(GL_ARRAY_BUFFER, q_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quads), quads, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindVertexArray(0);

    // 포스트 프로세싱 셰이더 설정
    post_shader->Use();
    post_shader->SetTex("screen_tex", 0);
    post_shader->SetVec2("screen_res", glm::vec2(WINDOW_WIDTH, WINDOW_HEIGHT));

    manager = std::make_unique<Manager>();

    auto map = std::make_shared<Map>();
    manager->SetRoot(map);

    RandomCubeFactory factory(10.f, 10.f, 10.f, 10.f, 1000);
    factory.GenerateCubes(*manager, lighting_shader->id, snow_vertices);

    std::vector<GLfloat> ground_vertices = {
        // ----- Front face (z = -1, normal = ( 0,  0, -1 )) -----
        -1.f, -0.5f, -1.f,   0.f,  0.f, -1.f,   0.3f, 0.3f, 0.3f,
        1.f, -0.5f, -1.f,   0.f,  0.f, -1.f,   0.3f, 0.3f, 0.3f,
        1.f,  0.5f, -1.f,   0.f,  0.f, -1.f,   0.3f, 0.3f, 0.3f,
        -1.f,  0.5f, -1.f,   0.f,  0.f, -1.f,   0.3f, 0.3f, 0.3f,

        // ----- Back face (z =  1, normal = ( 0,  0,  1 )) -----
        -1.f, -0.5f,  1.f,   0.f,  0.f,  1.f,   0.3f, 0.3f, 0.3f,
        1.f, -0.5f,  1.f,   0.f,  0.f,  1.f,   0.3f, 0.3f, 0.3f,
        1.f,  0.5f,  1.f,   0.f,  0.f,  1.f,   0.3f, 0.3f, 0.3f,
        -1.f,  0.5f,  1.f,   0.f,  0.f,  1.f,   0.3f, 0.3f, 0.3f,

        // ----- Left face (x = -1, normal = (-1, 0, 0)) -----
        -1.f, -0.5f, -1.f,  -1.f,  0.f,  0.f,   0.3f, 0.3f, 0.3f,
        -1.f, -0.5f,  1.f,  -1.f,  0.f,  0.f,   0.3f, 0.3f, 0.3f,
        -1.f,  0.5f,  1.f,  -1.f,  0.f,  0.f,   0.3f, 0.3f, 0.3f,
        -1.f,  0.5f, -1.f,  -1.f,  0.f,  0.f,   0.3f, 0.3f, 0.3f,

        // ----- Right face (x =  1, normal = ( 1, 0, 0)) -----
        1.f, -0.5f, -1.f,   1.f,  0.f,  0.f,   0.3f, 0.3f, 0.3f,
        1.f, -0.5f,  1.f,   1.f,  0.f,  0.f,   0.3f, 0.3f, 0.3f,
        1.f,  0.5f,  1.f,   1.f,  0.f,  0.f,   0.3f, 0.3f, 0.3f,
        1.f,  0.5f, -1.f,   1.f,  0.f,  0.f,   0.3f, 0.3f, 0.3f,

        // ----- Top face (y =  0.5, normal = (0, 1, 0)) -----
        -1.f,  0.5f, -1.f,   0.f,  1.f,  0.f,   0.3f, 0.3f, 0.3f,
        1.f,  0.5f, -1.f,   0.f,  1.f,  0.f,   0.3f, 0.3f, 0.3f,
        1.f,  0.5f,  1.f,   0.f,  1.f,  0.f,   0.3f, 0.3f, 0.3f,
        -1.f,  0.5f,  1.f,   0.f,  1.f,  0.f,   0.3f, 0.3f, 0.3f,

        // ----- Bottom face (y = -0.5, normal = (0, -1, 0)) -----
        -1.f, -0.5f, -1.f,   0.f, -1.f,  0.f,   0.3f, 0.3f, 0.3f,
        1.f, -0.5f, -1.f,   0.f, -1.f,  0.f,   0.3f, 0.3f, 0.3f,
        1.f, -0.5f,  1.f,   0.f, -1.f,  0.f,   0.3f, 0.3f, 0.3f,
        -1.f, -0.5f,  1.f,   0.f, -1.f,  0.f,   0.3f, 0.3f, 0.3f,
    };

    cam = std::make_unique<Camera>();
    last_frame = static_cast<GLfloat>(glfwGetTime());

    _color = glm::vec3(1.f, 1.f, 1.f);

    change_light = false;
    render = false;
    post_enable = 0;

    return true;
}

void App::Run()
{
    GLfloat curr_frame = static_cast<GLfloat>(glfwGetTime());
    dt = curr_frame - last_frame;

    ProcessInput(window);
    manager->Update(dt);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(render)
        Render();
    else
        glClearColor(0.f, 0.f, 0.f, 0.f);
    
    glfwPollEvents();
    glfwSwapBuffers(window);

    last_frame = curr_frame + target_frame_time;
}

void App::Render()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glClearColor(1.f - _color.x, 1.f - _color.y, 1.f - _color.z, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    lighting_shader->Use();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = cam->GetViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(cam->zoom),
        static_cast<GLfloat>(WINDOW_WIDTH) / static_cast<GLfloat>(WINDOW_HEIGHT),
        0.1f, 100.0f);

    lighting_shader->SetMat("proj", proj);
    lighting_shader->SetMat("view", view);
    lighting_shader->SetMat("model", model);

    lighting_shader->SetVec("light_pos", glm::vec3(0.f, 0.f, 0.f));
    lighting_shader->SetVec("view_pos", cam->pos);
    lighting_shader->SetVec("light_color", _color);

    lighting_shader->SetTex("enabled", post_enable);

    manager->Draw(view, proj);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    post_shader->Use();

    glBindVertexArray(q_vao);
    glDisable(GL_DEPTH_TEST);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, color_text);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(0);
}

void App::ProcessInput(GLFWwindow* window)
{
    GLfloat abs_dt = glm::abs(dt);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam->ProcessKeyboard(Camera::Movement::Forward, abs_dt);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam->ProcessKeyboard(Camera::Movement::Backward, abs_dt);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam->ProcessKeyboard(Camera::Movement::Left, abs_dt);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam->ProcessKeyboard(Camera::Movement::Right, abs_dt);
    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        GenerateRandomColor();

    static bool space_pressed = false;
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !space_pressed)
    {
        render = !render;
        space_pressed = true;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
        space_pressed = false;

    static bool p_key_pressed = false;
    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !p_key_pressed)
    {
        post_enable = post_enable > 0 ? 0 : 1;
        p_key_pressed = true;
    }
    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
        p_key_pressed = false;

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