#version 330 core

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_tex_coords;

out vec3 out_frag_pos;
out vec3 out_normal;
out vec2 out_tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
  out_frag_pos = vec3(model * vec4(in_pos, 1.0));
  out_normal = mat3(transpose(inverse(model))) * in_normal;
  out_tex_coords = in_tex_coords;

  gl_Position = proj * view * vec4(out_frag_pos, 1.0);
}