// Created on Fri Jan 10 2025
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

#version 330 core

layout(location = 0) in vec3 att_pos;
layout(location = 1) in vec3 att_norm;
layout(location = 2) in vec3 att_color;

out vec3 in_pos;
out vec3 in_norm;
out vec3 in_color;

// MVP
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
  in_pos = vec3(model * vec4(att_pos, 1.0));
  in_norm = normalize(mat3(transpose(inverse(model))) * att_norm);
  in_color = att_color;

  gl_Position = proj * view * model * vec4(in_pos, 1.0);
}