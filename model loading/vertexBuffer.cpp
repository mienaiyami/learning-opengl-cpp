#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() {
    // GlCall(glGenBuffers(1, &id));
}

VertexBuffer::VertexBuffer(const void *vertices, unsigned int size, bool deleteOnDeath) {
    this->dataSet = true;
    this->deleteOnDeath = deleteOnDeath;
    GlCall(glGenBuffers(1, &id));
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, id));
    GlCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
};

VertexBuffer::~VertexBuffer() {
    if (this->deleteOnDeath) {
        GlCall(glDeleteBuffers(1, &id));
        std::cout << "MESSAGE::VertexBuffer : VertexBuffer deleted " << id << std::endl;
    }
};

void VertexBuffer::setData(const void *vertices, unsigned int size, bool deleteOnDeath) {
    if (dataSet) {
        std::cout << "WARNING::VertexBuffer::setData : can only set data once" << std::endl;
        return;
    }
    this->dataSet = true;
    this->deleteOnDeath = deleteOnDeath;
    GlCall(glGenBuffers(1, &id));
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, id));
    GlCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
};

void VertexBuffer::bind() {
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}
void VertexBuffer::unbind() {
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}