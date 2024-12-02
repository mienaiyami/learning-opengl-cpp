// #pragma once

// #include "glmInclude.h"
// #include "myUtils.h"
// #include "shader.h"
// #include "vertexArray.h"
// #include "vertexBuffer.h"
// #include "elementBuffer.h"
// #include <vector>

// struct Vertex {
//     glm::vec3 Position;
//     glm::vec3 Normal;
//     glm::vec2 TextCoord;
// };
// struct Texture {
//     unsigned int id;
//     std::string type;
// };
// class Mesh {
// public:
//     std::vector<Vertex> vertices;
//     std::vector<unsigned int> indices;
//     std::vector<Texture> textures;

//     Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
//     void Draw(Shader &shader);

// private:
//     VertexBuffer VBO;
//     VertexArray VAO;
//     ElementBuffer EBO;

//     void setupMesh();
// };
