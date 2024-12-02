#pragma once

#include "myUtils.h"
#include <glad/glad.h>

class VertexBuffer {
private:
    unsigned int id;
    bool deleteOnDeath;
    bool dataSet = false;

public:
    VertexBuffer();
    VertexBuffer(const void *vertices, unsigned int size, bool deleteOnDeath = true);
    ~VertexBuffer();
    void bind();
    void setData(const void *vertices, unsigned int size, bool deleteOnDeath = true);
    void unbind();
};
