// Created on Sat Jan 04 2025
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

class Camera
{
public:
    inline static constexpr GLfloat YAW = -90.0f;
    inline static constexpr GLfloat PITCH = 0.0f;
    inline static constexpr GLfloat SPEED = 2.5f;
    inline static constexpr GLfloat SENSITIVITY = 0.1f;
    inline static constexpr GLfloat ZOOM = 45.0f;

    enum class Movement
    {
        Forward,
        Backward,
        Left,
        Right
    };

    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    GLfloat yaw;
    GLfloat pitch;
    
    GLfloat speed;
    GLfloat sensitivity;
    GLfloat zoom;

    Camera(glm::vec3 _pos = glm::vec3(0.0f, 0.0f, 3.0f), 
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
           GLfloat _yaw = YAW,
           GLfloat _pitch = PITCH) 
        : front(glm::vec3(0.0f, 0.0f, -1.0f)), 
          speed(SPEED), 
          sensitivity(SENSITIVITY), 
          zoom(ZOOM)
    {
        pos = _pos;
        world_up = up;
        yaw = _yaw;
        pitch = _pitch;
        UpdateVectors();
    }

    glm::mat4 GetViewMatrix();

    void ProcessKeyboard(Movement dir, GLfloat dt);
    void ProcessMouseMovement(GLfloat off_x, GLfloat off_y, GLboolean constrain_pitch = true);
    void ProcessMouseScroll(GLfloat off_y);

private:
    inline void UpdateVectors()
    {
        glm::vec3 _front(
            cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
            sin(glm::radians(pitch)),
            sin(glm::radians(yaw)) * cos(glm::radians(pitch))
        );

        this->front = glm::normalize(_front);

        right = glm::normalize(glm::cross(front, world_up));  
        up = glm::normalize(glm::cross(right, front));
    }
};