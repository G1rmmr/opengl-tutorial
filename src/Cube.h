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

#include <vector>
#include <array>
#include <random>
#include <unordered_map>
#include <string>

#include "Object.h"
#include "Manager.h"

class Cube : public Object
{
public:
    Cube(glm::vec3 _pos, glm::quat _rot, glm::vec3 _sc, GLuint _prog, const std::vector<GLfloat>& _vertices)
    : Object(_pos, _rot, _sc)
    {
        Init(_prog, _vertices);
    }

    void Draw(const glm::mat4& view, const glm::mat4& proj) override;
    void Update(GLfloat dt, const glm::mat4& world_form) override;

private:
    std::unordered_map<std::string_view, GLuint> uniforms;
    std::vector<GLfloat> vertices;

    // 6개 면 각각 4개 정점을 이웃한 2개 삼각형으로 구성
// face 당 2트라이앵글, 총 12트라이앵글, 36인덱스
std::array<GLuint, 36> indices = {
        // front face (정점: 0,1,2,3)
        0, 1, 2,
        2, 3, 0,

        // back face (정점: 4,5,6,7)
        4, 5, 6,
        6, 7, 4,

        // left face (정점: 8,9,10,11)
        8, 9, 10,
        10, 11, 8,

        // right face (정점: 12,13,14,15)
        12, 13, 14,
        14, 15, 12,

        // top face (정점: 16,17,18,19)
        16, 17, 18,
        18, 19, 16,

        // bottom face (정점: 20,21,22,23)
        20, 21, 22,
        22, 23, 20
    };


    void Init(GLuint _prog, const std::vector<GLfloat>& _vertices);
};

class RandomCubeFactory
{
public:
    RandomCubeFactory(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _min, size_t _count)
    : x_range(_x), y_range(_y), z_range(_z), min_distance(_min), count(_count)
    {

    }

    ~RandomCubeFactory() = default;

    void GenerateCubes(Manager& manager, GLuint prog, const std::vector<GLfloat>& _vertices)
    {
        std::vector<glm::vec3> generated_pos;
        generated_pos.reserve(count);

        for(size_t i = 0; i < count; ++i)
        {
            glm::vec3 pos = GenerateRandomPos(generated_pos);
            glm::quat rot = GenerateRandomRot();
            glm::vec3 sc(0.5f, 0.5f, 0.5f);

            auto rand_cube = std::make_shared<Cube>(pos, rot, sc, prog, _vertices);
            manager.AddChild(std::make_unique<Scene>(rand_cube));

            generated_pos.emplace_back(pos);
        }
    }

private:
    GLfloat x_range;
    GLfloat y_range;
    GLfloat z_range;
    GLfloat min_distance;

    size_t count;

    std::mt19937 rng{std::random_device{}()};

    std::uniform_real_distribution<GLfloat> dist_x{-x_range, x_range};
    std::uniform_real_distribution<GLfloat> dist_y{3.f, y_range};
    std::uniform_real_distribution<GLfloat> dist_z{-z_range, z_range};
    std::uniform_real_distribution<GLfloat> dist_angle{-180.0f, 180.0f};

    glm::vec3 GenerateRandomPos(const std::vector<glm::vec3>& _pos)
    {
        const GLint max_attempts = 1000;

        for(GLint i = 0; i < max_attempts; ++i)
        {
            glm::vec3 candidate(dist_x(rng), dist_y(rng), dist_z(rng));

            GLboolean is_valid = true;
            for(const auto& p : _pos)
            {
                if(glm::distance(candidate, p) < min_distance)
                {
                    is_valid = false;
                    break;
                }
            }

            if(is_valid)
                return candidate;
        }
        return glm::vec3(dist_x(rng), dist_y(rng), dist_z(rng));
    }

    glm::quat GenerateRandomRot()
    {
        GLfloat yaw = glm::radians(dist_angle(rng));
        GLfloat pitch = glm::radians(dist_angle(rng));
        GLfloat roll = glm::radians(dist_angle(rng));
        return glm::quat(glm::vec3(pitch, yaw, roll));
    }
};