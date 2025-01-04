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

#pragma once

#include <string>

#include "glad.h"
#include <glm/gtc/type_ptr.hpp>

struct Shader
{
    unsigned int id;

    Shader(const char* vtx_path, const char* frag_path);

    void Use();
    void SetMat(const std::string& name, const glm::mat4& mat) const;
    void SetVec(const std::string &name, const glm::vec3& vec) const;
};