#pragma once

#include <debuger.h>

class vertex_buffer {
private:
	unsigned int m_rendererID;

public:
	vertex_buffer(const void* data, unsigned int size) {
		GLCall(glGenBuffers(1, &m_rendererID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	~vertex_buffer() {
		GLCall(glDeleteBuffers(1, &m_rendererID));
	}

	void bind() const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
	}

	void unbind() const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
};