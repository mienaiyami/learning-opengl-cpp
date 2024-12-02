#include "vertexArray.h"

VertexArray::VertexArray(unsigned int stride, unsigned int length) : stride(stride) {
    attrData.resize(length);
    GlCall(glGenVertexArrays(1, &id));
    GlCall(glBindVertexArray(id));
};
VertexArray::~VertexArray() {
    GlCall(glDeleteVertexArrays(1, &id));
    std::cout << "MESSAGE::VertexArray : vertexarray deleted " << id << std::endl;
}
void VertexArray::attrPointer(unsigned int index, int size) {
    if (index > attrData.size() - 1) {
        std::cout << "ERROR::VertexArray : index(" << index << ") greater than size of vector attrData(" << attrData.size() << ")." << std::endl;
        return;
    }
    unsigned int pointerSize = 0;
    for (size_t i = 0; i < index; i++) {
        pointerSize += attrData[i];
    }
    attrData[index] = size;
    GlCall(glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void *)(pointerSize * sizeof(float))));
    GlCall(glEnableVertexAttribArray(index));
};
void VertexArray::bind() {
    GlCall(glBindVertexArray(id));
};