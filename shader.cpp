#include "shader.h"
#include "renderer.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

#include <GL/glew.h>

shader::shader(const std::string& filepath) : m_filepath(filepath), m_rendererID(0) {
    shader_program_source source = parse_shader(filepath);
    m_rendererID = create_shader(source.VertexSource, source.FragmentSource);
}

shader::~shader() {
    GLCall(glDeleteProgram(m_rendererID));
}

void shader::bind() const {
    GLCall(glUseProgram(m_rendererID));
}

void shader::unbind() const {
    GLCall(glUseProgram(0));
}

void shader::set_uniform1i(const std::string& name, int v0) {
    GLCall(glUniform1i(this->get_uniform_location(name), v0));
}

void shader::set_uniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(this->get_uniform_location(name), v0, v1, v2, v3));
}

shader_program_source shader::parse_shader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::stringstream ss[2];    // can be replaced with std::vector<std::string>
    std::string line;
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[int(type)] << line << '\n';
        }
    }

    return shader_program_source{ ss[0].str(), ss[1].str() };
}

unsigned int shader::compile_shader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();   // source should be alive
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile a " <<
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int shader::create_shader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vShader = compile_shader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fShader = compile_shader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glUseProgram(0);
    glDeleteShader(vShader);
    glDeleteShader(fShader);

    return program;
}

unsigned int shader::get_uniform_location(const std::string& name) {
    if (m_location_cache.find(name) != m_location_cache.end())
        return m_location_cache[name];

    int location = glGetUniformLocation(m_rendererID, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist\n";
        
    m_location_cache[name] = location;
    return location;
}