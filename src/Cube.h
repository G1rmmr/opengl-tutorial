// Created on Sun Jan 05 2025
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

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <array>
#include <random>

#include "Object.h"
#include "Manager.h"

class Cube : public Object
{
public:
    Cube(glm::vec3 _pos, glm::quat _rot, glm::vec3 _sc)
    : Object(_pos, _rot, _sc)
    {
        Init();
    }

    void Draw(GLuint shader_prog, const glm::mat4& view, const glm::mat4& proj) override;
    void Update(GLfloat dt, const glm::mat4& world_form) override;

private:
    std::array<GLfloat, 48> vertices = {
        -0.5f, -0.5f, -0.5f,  1.f, 1.f, 1.f,
         0.5f, -0.5f, -0.5f,  1.f, 1.f, 1.f,
         0.5f,  0.5f, -0.5f,  1.f, 1.f, 1.f,
        -0.5f,  0.5f, -0.5f,  1.f, 1.f, 1.f,
        -0.5f, -0.5f,  0.5f,  1.f, 1.f, 1.f,
         0.5f, -0.5f,  0.5f,  1.f, 1.f, 1.f,
         0.5f,  0.5f,  0.5f,  1.f, 1.f, 1.f,
        -0.5f,  0.5f,  0.5f,  1.f, 1.f, 1.f
    };

    std::array<GLuint, 36> indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        4, 5, 1, 1, 0, 4,
        6, 7, 3, 3, 2, 6,
        4, 7, 3, 3, 0, 4,
        5, 6, 2, 2, 1, 5
    };

    void Init();
};

class RandomCubeFactory
{
public:
    RandomCubeFactory(GLfloat _y, GLfloat _x, GLfloat _z, size_t _count)
    : fixed_y(_y), x_range(_x), z_range(_z), count(_count)
    {

    }

    ~RandomCubeFactory() = default;

    void GenerateCubes(Manager& manager)
    {
        for(size_t i = 0; i < count; ++i)
        {
            glm::vec3 pos = GenerateRandomPos();
            glm::quat rot = GenerateRandomRot();
            glm::vec3 sc(1.0f, 1.0f, 1.0f);

            auto rand_cube = std::make_shared<Cube>(pos, rot, sc);
            manager.AddChild(std::make_unique<Scene>(rand_cube));
        }
    }

private:
    GLfloat fixed_y;
    GLfloat x_range, z_range;

    size_t count;

    std::mt19937 rng{std::random_device{}()};

    std::uniform_real_distribution<GLfloat> dist_x{-x_range, x_range};
    std::uniform_real_distribution<GLfloat> dist_z{-z_range, z_range};
    std::uniform_real_distribution<GLfloat> dist_angle{-180.0f, 180.0f};

    glm::vec3 GenerateRandomPos()
    {
        return glm::vec3(dist_x(rng), fixed_y, dist_z(rng));
    }

    glm::quat GenerateRandomRot()
    {
        float yaw = glm::radians(dist_angle(rng));
        float pitch = glm::radians(dist_angle(rng));
        float roll = glm::radians(dist_angle(rng));
        return glm::quat(glm::vec3(pitch, yaw, roll));
    }
};