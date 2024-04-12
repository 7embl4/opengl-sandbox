#pragma once

#include <debuger.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glew.h>

class texture {
private:
	unsigned int m_rendererID;
	std::string m_filepath;
	unsigned char* m_localbuffer;
	int m_width, m_height, m_bpp;

public:
	texture(const std::string& filepath) 
		: m_rendererID(0)
		, m_filepath(filepath)
		, m_localbuffer(nullptr)
		, m_width(0)
		, m_height(0)
		, m_bpp(0)
	{
		stbi_set_flip_vertically_on_load(1);
		m_localbuffer = stbi_load(filepath.c_str(), &m_width, &m_height, &m_bpp, 4);

		GLCall(glGenTextures(1, &m_rendererID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localbuffer));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		if (m_localbuffer) {
			stbi_image_free(m_localbuffer);
		}
	}

	~texture() {
		GLCall(glDeleteTextures(1, &m_rendererID));
	}

	void bind(unsigned int slot = 0) const {
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
	}

	void unbind() const {
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	int get_width() const { return m_width; }
	int get_height() const { return m_height; }
};