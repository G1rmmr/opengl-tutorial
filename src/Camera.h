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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    inline static constexpr float YAW = -90.0f;
    inline static constexpr float PITCH = 0.0f;
    inline static constexpr float SPEED = 2.5f;
    inline static constexpr float SENSITIVITY = 0.1f;
    inline static constexpr float ZOOM = 45.0f;

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

    float yaw;
    float pitch;
    
    float speed;
    float sensitivity;
    float zoom;

    Camera(glm::vec3 _pos = glm::vec3(0.0f, 0.0f, 3.0f), 
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
           float _yaw = YAW,
           float _pitch = PITCH) 
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

    void ProcessKeyboard(Movement dir, float dt);
    void ProcessMouseMovement(float off_x, float off_y, bool constrain_pitch = true);
    void ProcessMouseScroll(float off_y);

private:
    inline void UpdateVectors()
    {
        glm::vec3 front;

        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        front = glm::normalize(front);
        right = glm::normalize(glm::cross(front, world_up));  
        up = glm::normalize(glm::cross(right, front));
    }
};