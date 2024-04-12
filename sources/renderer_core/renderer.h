#pragma once

#include "vertex_array.h"
#include "index_buffer.h"
#include <shader.h>
#include <debuger.h>

#include <GL/glew.h>

class renderer {
public:
    void clear() const {
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
    }

    void draw(const vertex_array& vao, const index_buffer& ibo, const shader& sh) const {
        sh.bind();
        vao.bind();
        ibo.bind();
        GLCall(glDrawElements(GL_TRIANGLES, ibo.get_count(), GL_UNSIGNED_INT, nullptr));
    }
};