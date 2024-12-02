#pragma once

#include <glad/glad.h>
#include <iostream>
#include "stb_image.h"
#include <vector>

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