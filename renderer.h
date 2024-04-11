#pragma once

#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();
bool GLLogCall(const char*, const char*, int);

class renderer {
public:
    void clear() const;
    void draw(const vertex_array& vao, const index_buffer& ibo, const shader& sh) const;
};