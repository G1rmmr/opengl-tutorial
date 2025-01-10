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

  vec3 norm = normalize(in_norm);
  vec3 light_dir = normalize(light_pos - in_pos);

  float _diff = dot(norm, light_dir);
  vec3 diff = _diff * light_color;

  vec3 result = (amb + diff) * in_color;
  frag_color = vec4(result, 1.0);
}