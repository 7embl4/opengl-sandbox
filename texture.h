#pragma once

#include "renderer.h"

class texture {
private:
	unsigned int m_rendererID;
	std::string m_filepath;
	unsigned char* m_localbuffer;
	int m_width, m_height, m_bpp;

public:
	texture(const std::string& filepath);
	~texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	int get_width() const { return m_width; }
	int get_height() const { return m_height; }
};