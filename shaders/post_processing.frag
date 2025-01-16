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

in vec2 in_tex_coords;

out vec4 frag_color;

uniform sampler2D screen_tex;
uniform vec2 screen_res;

float rand(vec2 co) {
  return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
  vec3 color = texture(screen_tex, in_tex_coords).rgb;

  float line_thick = 1.0;
  float intensity = 0.2;

  float y = in_tex_coords.y * screen_res.y;

  if (mod(y, 2.0) < line_thick)
    color *= (1.0 - intensity);

  float noise_strength = 0.05;
  float noise = rand(in_tex_coords) * noise_strength;
  color += vec3(noise);

  frag_color = vec4(color, 1.0);
}
