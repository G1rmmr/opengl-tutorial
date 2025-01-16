// Created on Thu Jan 16 2025
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

layout(location = 0) in vec2 att_pos;
layout(location = 1) in vec2 att_tex_coords;

out vec2 in_tex_coords;

void main() {
  in_tex_coords = att_tex_coords;
  gl_Position = vec4(att_pos, 0.0, 1.0);
}