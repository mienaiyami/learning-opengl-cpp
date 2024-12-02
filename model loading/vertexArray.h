#pragma once

#include "myUtils.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class VertexArray {
private:
    unsigned int stride = 0;
    bool dataSet = false;
    bool deleteOnDeath;
    std::vector<int> attrData;

public:
    unsigned int id;
    VertexArray();
    VertexArray(unsigned int stride, unsigned int length,bool deleteOnDeath=true);
    ~VertexArray();
    // void attrPointer(unsigned int index, int size);
    void attrPointer(unsigned int index, int size, void *pointer);
    void setData(unsigned int stride, unsigned int length,bool deleteOnDeath=true);
    void bind();
    void unbind();
};