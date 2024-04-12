#pragma once

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include <debuger.h>

class vertex_array {
private:
	unsigned int m_rendererID;

public:
	vertex_array() {
		GLCall(glGenVertexArrays(1, &m_rendererID));
	}

	~vertex_array() {
		GLCall(glDeleteVertexArrays(1, &m_rendererID));
	}

	void bind() const {
		GLCall(glBindVertexArray(m_rendererID));
	}

	void unbind() const {
		GLCall(glBindVertexArray(0));
	}

	void add_buffer(const vertex_buffer& buffer, const vertex_buffer_layout& layout) {
		this->bind();
		buffer.bind();
		const auto& elements = layout.get_elements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i != elements.size(); ++i) {
			const auto& element = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(
				i,
				element.count,
				element.type,
				element.normalized,
				layout.get_stride(),
				(const void*)offset
			));
			offset += element.count * vertex_buffer_element::get_size_of_type(element.type);
		}
	}
};