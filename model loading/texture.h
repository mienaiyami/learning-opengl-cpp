#pragma once

#include "myUtils.h"
#include "stb_image.h"
#include <glad/glad.h>
#include <iostream>

class Textures {
private:
    int width, height, nrChannels;

public:
    std::vector<unsigned int> textures;
    ~Textures();
    void newTexture(const char *img, bool isPng = false);
    void useTexture(unsigned int index);
    void useAllTextures();
};