#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void *vertices, unsigned int size) {
    GlCall(glGenBuffers(1, &id));
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, id));
    GlCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
};

VertexBuffer::~VertexBuffer() {
    GlCall(glDeleteBuffers(1, &id));
    std::cout << "MESSAGE::VertexBuffer : VertexBuffer deleted " << id << std::endl;
};

void VertexBuffer::bind() {
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}
void VertexBuffer::unbind() {
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}