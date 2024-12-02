#pragma once

#include "myUtils.h"
#include <glad/glad.h>

class VertexBuffer {
private:
    unsigned int id;
public:
    VertexBuffer(const void* vertices, unsigned int size);
    ~VertexBuffer();
    void bind();
    void unbind();
};
