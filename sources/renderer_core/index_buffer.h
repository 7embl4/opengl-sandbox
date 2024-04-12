#pragma once

#include <debuger.h>

class index_buffer {
private:
	unsigned int m_rendererID;
	unsigned int m_count;

public:
	index_buffer(const unsigned int* indices, unsigned int count) : m_count(count) {
		GLCall(glGenBuffers(1, &m_rendererID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
	}
	~index_buffer() {
		GLCall(glDeleteBuffers(1, &m_rendererID));
	}

	void bind() const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
	}

	void unbind() const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	unsigned int get_count() const { return m_count; }
};