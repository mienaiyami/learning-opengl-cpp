
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <vector>
#ifndef TEXTURE_H
#define TEXTURE_H

class Textures {
private:
    int width, height, nrChannels;
public:
    std::vector<unsigned int> textures;
    void newTexture(const char* img,GLenum format=GL_RGB, bool vFlip=false) {
        stbi_set_flip_vertically_on_load(vFlip);
        unsigned char* data = stbi_load(img, &width, &height, &nrChannels, 0);
        if (data) {
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,format,GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            std::cout << "added new texture: " << img << std::endl;
            textures.push_back(texture);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }
    void useTexture(unsigned int index) {
        glActiveTexture(GL_TEXTURE0+index);
        glBindTexture(GL_TEXTURE_2D, textures[index]);
    };
    void useAllTextures() {
        for (size_t i = 0; i < textures.size(); i++){
            useTexture(i);
        }
    };
};
#endif
