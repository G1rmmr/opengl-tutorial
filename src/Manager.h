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

#pragma once

#include <vector>
#include <memory>

#include "Object.h"

struct Scene
{
    std::shared_ptr<Object> object;
    std::vector<std::shared_ptr<Scene>> children;

    Scene(std::shared_ptr<Object> obj) : object(obj) {}

    void AddChild(const Scene& child)
    {
        children.emplace_back(std::make_shared<Scene>(child));
    }

    void Draw(GLuint shader_prog, const glm::mat4& parent_form, const glm::mat4& view, const glm::mat4& proj)
    {
        glm::mat4 world_form = parent_form * object->GetMatrix();
        object->Draw(shader_prog, view, proj);

        for(auto& child : children)
            child->Draw(shader_prog, world_form, view, proj);
    }
};


class Manager
{
public:
    Manager()
    {
        scene = std::make_unique<Scene>(nullptr);
    }

    void SetRoot(std::shared_ptr<Object> root)
    {
        scene->object = root;
    }

    void AddChild(const std::shared_ptr<Scene>& child)
    {
        scene->children.emplace_back(child);
    }

    void AddNode(const std::shared_ptr<Scene>& parent, const std::shared_ptr<Scene>& child)
    {
        parent->children.emplace_back(child);
    }

    void Draw(GLuint shader_prog, const glm::mat4& view, const glm::mat4& proj)
    {
        if(scene && scene->object)
        {
            glm::mat4 id = glm::mat4(1.0f);
            scene->Draw(shader_prog, id, view, proj);
        }
    }

private:
    std::unique_ptr<Scene> scene;
};