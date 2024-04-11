#pragma once

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class vertex_array {
private:
	unsigned int m_rendererID;

public:
	vertex_array();
	~vertex_array();

	void bind() const;
	void unbind() const;

	void add_buffer(const vertex_buffer& buffer, const vertex_buffer_layout& layout);
};