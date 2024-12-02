#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) : VBO(), VAO(), EBO() {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    setupMesh();
}
void Mesh::setupMesh() {
    VAO.setData(sizeof(Vertex) / sizeof(float), 3,false);
    VBO.setData(&vertices[0], vertices.size() * sizeof(Vertex),false);
    EBO.setData(&indices[0],indices.size(),false);

    VAO.attrPointer(0, 3, (void *)(0));
    VAO.attrPointer(1, 3, (void *)offsetof(Vertex, Normal));
    VAO.attrPointer(2, 2, (void *)offsetof(Vertex, TexCoords));
    VAO.unbind();

}
void Mesh::Draw(Shader &shader) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = textures[i].type;
        if (name == "diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "specular")
            number = std::to_string(specularNr++);

        shader.setFloat(("material." + name).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    VAO.bind();
    GlCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
    VAO.unbind();

    glActiveTexture(GL_TEXTURE0);
}

//no class vbo

// void Mesh::Draw(Shader &shader){
//         unsigned int diffuseNr  = 1;
//         unsigned int specularNr = 1;
//         unsigned int normalNr   = 1;
//         unsigned int heightNr   = 1;
//         for(unsigned int i = 0; i < textures.size(); i++){
//             glActiveTexture(GL_TEXTURE0 + i);
//             std::string number;
//             std::string name = textures[i].type;
//             if(name == "texture_diffuse")
//                 number = std::to_string(diffuseNr++);
//             else if(name == "texture_specular")
//                 number = std::to_string(specularNr++); // transfer unsigned int to string
//             else if(name == "texture_normal")
//                 number = std::to_string(normalNr++); // transfer unsigned int to string
//              else if(name == "texture_height")
//                 number = std::to_string(heightNr++); // transfer unsigned int to string

//             shader.setInt((name + number).c_str(),i);
//             glBindTexture(GL_TEXTURE_2D, textures[i].id);
//         }
        
//         // draw mesh
//         glBindVertexArray(VAO);
//         glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
//         glBindVertexArray(0);
        
//         glActiveTexture(GL_TEXTURE0);
// }

// void Mesh::setupMesh() {

//     // create buffers/arrays
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);
//     glGenBuffers(1, &EBO);

//     glBindVertexArray(VAO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

//     // vertex Positions
//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
//     // vertex normals
//     glEnableVertexAttribArray(1);
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
//     // vertex texture coords
//     glEnableVertexAttribArray(2);
//     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));
//     glBindVertexArray(0);
// }
