#pragma once

#include "assimpImport.h"
#include "mesh.h"
#include "myUtils.h"
#include "stb_image.h"

using namespace std;
// using namespace Assimp;

class Model {
private:
    vector<Mesh> meshes;
    string directory;
    vector<Texture> textures_loaded; 

    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

public:
    Model(const string &path) {
        loadModel(path);
    }
    void Draw(Shader &shader);

};