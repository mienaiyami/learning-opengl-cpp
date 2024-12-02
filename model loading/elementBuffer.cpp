#include "elementBuffer.h"

#include "renderer.h"

ElementBuffer::ElementBuffer() {
}

ElementBuffer::ElementBuffer(const unsigned int *data, unsigned int count, bool deleteOnDeath) {
    this->dataSet = true;
    this->deleteOnDeath = deleteOnDeath;
    this->count = count;
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    GlCall(glGenBuffers(1, &id));
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
    GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));
}

void ElementBuffer::setData(const unsigned int *data, unsigned int count, bool deleteOnDeath) {
    if (dataSet) {
        std::cout << "WARNING::ElementBuffer::setData : can only set data once" << std::endl;
        return;
    }
    this->dataSet = true;
    this->deleteOnDeath = deleteOnDeath;
    this->count = count;
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    GlCall(glGenBuffers(1, &id));
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
    GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));
}

ElementBuffer::~ElementBuffer() {
    if (this->deleteOnDeath) {
        GlCall(glDeleteBuffers(1, &id));
        std::cout << "MESSAGE::ElementBuffer : ElementBuffer deleted " << id << std::endl;
    }
}

void ElementBuffer::bind() const {
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

void ElementBuffer::unbind() const {
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
