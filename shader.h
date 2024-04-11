#pragma once

#include <string>
#include <unordered_map>

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
	shader(const std::string& filepath);
	~shader();

	void bind() const;
	void unbind() const;

	// Set uniforms
	void set_uniform1i(const std::string& name, int v0);
	void set_uniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	shader_program_source parse_shader(const std::string& filepath);
	unsigned int compile_shader(unsigned int type, const std::string& source);
	unsigned int create_shader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int get_uniform_location(const std::string& name);
};