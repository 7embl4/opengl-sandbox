#include "vertex_buffer.h"

#include "renderer.h"

vertex_buffer::vertex_buffer(const void* data, unsigned int size) {
    GLCall(glGenBuffers(1, &m_rendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

vertex_buffer::~vertex_buffer() {
    GLCall(glDeleteBuffers(1, &m_rendererID));
}

void vertex_buffer::bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void vertex_buffer::unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}