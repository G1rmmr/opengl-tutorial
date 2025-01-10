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

#include "Shader.h"

#include <fstream>
#include <sstream>
#include <cstdio>

Shader::Shader(const std::string_view& vtx_path, const std::string_view& frag_path)
{
    std::string vtx_code;
    std::string frag_code;

    std::ifstream v_shader;
    std::ifstream f_shader;

    v_shader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    f_shader.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try 
    {
        v_shader.open(vtx_path.data());
        f_shader.open(frag_path.data());
        std::stringstream v_stream, f_stream;

        v_stream << v_shader.rdbuf();
        f_stream << f_shader.rdbuf();		

        v_shader.close();
        f_shader.close();

        vtx_code = v_stream.str();
        frag_code = f_stream.str();
    }
    catch (std::ifstream::failure& e)
    {
        fprintf(stderr, "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n");
        return;
    }

    if (vtx_code.empty() || frag_code.empty())
    {
        fprintf(stderr, "ERROR::SHADER::EMPTY_FILE_CONTENT\n");
        return;
    }

    const GLchar* v_shader_code = vtx_code.c_str();
    const GLchar* f_shader_code = frag_code.c_str();

    GLuint vertex;
    GLuint fragment;
    GLint success;
    GLchar info[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &v_shader_code, NULL);
    glCompileShader(vertex);
    
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, info);
        fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n : %s\n", info);
        fprintf(stderr, "VERTEX SHADER CODE:\n%s\n", v_shader_code);
        return;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &f_shader_code, NULL);
    glCompileShader(fragment);
    
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, info);
        fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n : %s\n", info);
        fprintf(stderr, "FRAGMENT SHADER CODE:\n%s\n", f_shader_code);
        return;
    }

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 512, NULL, info);
        fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n : %s\n", info);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Use()
{
    glUseProgram(id);
}

void Shader::SetMat(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()),
        1, GL_FALSE, &mat[0][0]);
}

void Shader::SetVec(const std::string& name, const glm::vec3& vec) const
{
    glUniform3fv(glGetUniformLocation(id, name.c_str()),
        1, glm::value_ptr(vec));
}