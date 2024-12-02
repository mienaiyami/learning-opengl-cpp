#pragma once

#include "GLFWInitiate.h"
#include "assimpImport.h"
#include "camera.h"
#include "elementBuffer.h"
#include "glmInclude.h"
#include "model.h"
#include "myUtils.h"
#include "shader.h"
#include "texture.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Renderer {
private:
public:
    void draw(Shader &shader, VertexArray &vao, GLint first, GLsizei count);
    void draw(Shader &shader, ElementBuffer &ebo, GLsizei count);
    void drawGrid(int numbers, Shader &shader, VertexArray &vao, glm::mat4 &projection, glm::mat4 &view);
    void clear();
};
