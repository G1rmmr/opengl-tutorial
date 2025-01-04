#version 330 core

out vec4 out_frag_color;

in vec3 out_frag_pos;
in vec3 out_normal;
in vec2 out_tex_coords;

uniform vec3 light_pos;
uniform vec3 light_color;
uniform vec3 view_pos;
uniform vec3 object_color;

void main() {
  float _amb = 0.1;
  vec3 amb = _amb * light_color;

  vec3 norm = normalize(out_normal);
  vec3 light_dir = normalize(light_pos - out_frag_pos);
  float _diff = max(dot(norm, light_dir), 0.0);
  vec3 diff = _diff * light_color;

  vec3 view_dir = normalize(view_pos - out_frag_pos);
  vec3 reflect_dir = reflect(-light_dir, norm);
  float _spec = 0.5 * pow(max(dot(view_dir, reflect_dir), 0.0), 32);
  vec3 spec = _spec * light_color;

  vec3 result = (amb + diff + spec) * object_color;
  out_frag_color = vec4(result, 1.0);
}