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

in vec3 in_pos;
in vec3 in_norm;
in vec3 in_color;

out vec4 frag_color;

uniform vec3 light_pos;
uniform vec3 light_color;

uniform vec3 view_pos;

void main() {
  vec3 amb = 0.1 * light_color;

  vec3 light_dir = normalize(light_pos - in_pos);
  float _diff = max(0.0, dot(in_norm, light_dir));
  vec3 diff = _diff * light_color;

  vec3 result = (amb + diff) * in_color;
  frag_color = vec4(result, 1.0);
}