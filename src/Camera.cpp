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

#include "Camera.h"

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(pos, pos + front, up);
}

void Camera::ProcessKeyboard(Movement dir, GLfloat dt)
{
    GLfloat vel = speed * dt;

    switch(dir)
    {
    case Movement::Forward:
        pos += front * vel;
        break;
        
    case Movement::Backward:
        pos -= front * vel;
        break;
        
    case Movement::Left:
        pos -= right * vel;
        break;

    case Movement::Right:
        pos += right * vel;
        break;
    default:
        break;
    }
}

void Camera::ProcessMouseMovement(
    GLfloat off_x, GLfloat off_y, GLboolean constrain_pitch)
{
    off_x *= sensitivity;
    off_y *= sensitivity;

    yaw += off_x;
    pitch += off_y;

    if(constrain_pitch)
    {
        if(pitch > 89.0f)
            pitch = 89.0f;

        if(pitch < -89.0f)
            pitch = -89.0f;
    }

    UpdateVectors();
}

void Camera::ProcessMouseScroll(GLfloat off_y)
{
    zoom -= off_y;

    if(zoom < 1.0f)
        zoom = 1.0f;
    if(zoom > 45.0f)
        zoom = 45.0f;
}