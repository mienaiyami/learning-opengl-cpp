#pragma once

#include "elementBuffer.h"
#include "glmInclude.h"
#include "myUtils.h"
#include "shader.h"
#include "vertexArray.h"
#include "vertexBuffer.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};
class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader &shader);

private:
    // unsigned int VBO, VAO, EBO;
    VertexBuffer VBO;
    VertexArray VAO;
    ElementBuffer EBO;

    void setupMesh();
};
