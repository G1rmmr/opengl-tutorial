// Created on Tue Jan 07 2025
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

#include "Cube.h"

void Cube::Draw(const glm::mat4& view, const glm::mat4& proj)
{
    this->UpdateMatrix();

    glUniformMatrix4fv(mat_loc, 1, GL_FALSE, &this->mat[0][0]);
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, &proj[0][0]);
    
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Cube::Update(GLfloat dt, const glm::mat4& world_form)
{
    Rotate(10.0f * dt, {0.f, 1.f, 0.f});

    glm::vec3 translation(-0.5f * dt, -2.f * dt, -1.f * dt);
    this->mat = glm::translate(this->mat, translation);
}

void Cube::Init(GLuint _prog, const std::vector<GLfloat>& _vertices)
{
    shader_prog = _prog;
    vertices = _vertices;
    
    mat_loc = glGetUniformLocation(shader_prog, "model");
    view_loc = glGetUniformLocation(shader_prog, "view");
    proj_loc = glGetUniformLocation(shader_prog, "proj");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_DYNAMIC_DRAW);

    // layouts
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}