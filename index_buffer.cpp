#include "index_buffer.h"

#include "renderer.h"

index_buffer::index_buffer(const unsigned int* indices, unsigned int count) : m_count(count) {
    GLCall(glGenBuffers(1, &m_rendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
}

index_buffer::~index_buffer() {
    GLCall(glDeleteBuffers(1, &m_rendererID));
}

void index_buffer::bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
}

void index_buffer::unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}