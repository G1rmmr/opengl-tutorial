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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

class Object
{
public:
    Object() : pos(0.0f), rot(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), sc(1.0f)
    {
        UpdateMatrix();
    }

    Object(glm::vec3 _pos, glm::quat _rot, glm::vec3 _sc)
    : pos(_pos), rot(_rot), sc(_sc)
    {
        UpdateMatrix();
    }

    virtual ~Object()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    }

    inline void SetPos(const glm::vec3& _pos)
    {
        pos = _pos;
    }

    inline void SetRot(const glm::vec3& _rot)
    { 
        rot = glm::quat(glm::radians(_rot));
    }

    inline void Rotate(GLfloat angle, const glm::vec3& axis)
    {
        glm::quat delta = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
        rot = delta * rot;
    }

    inline void SetScale(const glm::vec3& _sc)
    {
        sc = _sc;
    }

    inline glm::mat4 GetMatrix() const
    {
        return mat;
    }

    virtual void Draw(GLuint shader_prog, const glm::mat4& view, const glm::mat4& proj) = 0;
    virtual void Update(GLfloat dt, const glm::mat4& world_form) = 0;

protected:
    glm::mat4 mat;

    glm::quat rot;

    glm::vec3 pos;
    glm::vec3 sc;

    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    inline void UpdateMatrix()
    {
        mat = glm::mat4(1.0f);
        mat = glm::translate(mat, pos);
        mat *= glm::toMat4(rot);
        mat = glm::scale(mat, sc);
    }
};