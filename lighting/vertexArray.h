#include "myUtils.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <vector>

class VertexArray {
private:
    unsigned int stride = 0;
    std::vector<int> attrData;

public:
    unsigned int id;
    VertexArray(unsigned int stride, unsigned int length);
    ~VertexArray();
    void attrPointer(unsigned int index, int size);
    void bind();
};