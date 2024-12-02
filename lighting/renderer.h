#pragma once

#include "GLFWInitiate.h"
#include "camera.h"
#include "myUtils.h"
#include "shader.h"
#include "texture.h"
#include "vertexArray.h"
#include "vertexBuffer.h"
#include "glmInclude.h"
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glad/glad.h>

class Renderer {
private:
public:
    void draw(Shader &shader, VertexArray &vao, GLint first, GLsizei count);
    void drawGrid(int numbers, Shader &shader, VertexArray &vao, glm::mat4 &projection, glm::mat4 &view);
    void importModel(const std::string& pFile);
    void clear();
};
