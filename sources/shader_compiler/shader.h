#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <string>
#include <unordered_map>

#include <debuger.h>

#include <GL/glew.h>
#include <glm/glm.hpp>

struct shader_program_source {
	std::string VertexSource;
	std::string FragmentSource;
};

class shader {
private:
	std::string m_filepath;
	unsigned int m_rendererID;
	std::unordered_map<std::string, int> m_location_cache;

public:
	shader(const std::string& filepath) : m_filepath(filepath), m_rendererID(0) {
		shader_program_source source = parse_shader(filepath);
		m_rendererID = create_shader(source.VertexSource, source.FragmentSource);
	}

	~shader() {
		GLCall(glDeleteProgram(m_rendererID));
	}

	void bind() const {
		// Optimization: If shader is already bound, don't rebind it one more time
		GLCall(glUseProgram(m_rendererID));
	}

	void unbind() const {
		GLCall(glUseProgram(0));
	}

	// Set uniforms
	void set_uniform1i(const std::string& name, int v0) {
		GLCall(glUniform1i(this->get_uniform_location(name), v0));
	}

	void set_uniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
		GLCall(glUniform4f(this->get_uniform_location(name), v0, v1, v2, v3));
	}

	void set_uniformMat4f(const std::string& name, const glm::mat4& matrix) {
		GLCall(glUniformMatrix4fv(this->get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]));
	}

private:
	shader_program_source parse_shader(const std::string& filepath) {
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

	unsigned int compile_shader(unsigned int type, const std::string& source) {
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

	unsigned int create_shader(const std::string& vertexShader, const std::string& fragmentShader) {
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
	
	unsigned int get_uniform_location(const std::string& name) {
		if (m_location_cache.find(name) != m_location_cache.end())
			return m_location_cache[name];

		int location = glGetUniformLocation(m_rendererID, name.c_str());
		if (location == -1)
			std::cout << "Warning: uniform '" << name << "' doesn't exist\n";

		m_location_cache[name] = location;
		return location;
	}
};