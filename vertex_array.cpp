#include "vertex_array.h"
#include "renderer.h"

vertex_array::vertex_array() {
	GLCall(glGenVertexArrays(1, &m_rendererID));
}

vertex_array::~vertex_array() {
	GLCall(glDeleteVertexArrays(1, &m_rendererID));
}

void vertex_array::bind() const {
	GLCall(glBindVertexArray(m_rendererID));
}

void vertex_array::unbind() const {
	GLCall(glBindVertexArray(0));
}

void vertex_array::add_buffer(const vertex_buffer& buffer, const vertex_buffer_layout& layout) {
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
