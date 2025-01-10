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
  in_norm = mat3(transpose(inverse(model))) * att_norm;
  in_color = att_color;

  gl_Position = proj * view * model * vec4(in_pos, 1.0);
}