#include "texture.h"

Textures::~Textures() {

}

void Textures::newTexture(const char *img, bool isPng) {
    if (isPng)
        stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(img, &width, &height, &nrChannels, 0);
    if (data) {
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, isPng ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "MESSAGE::Textures : added new texture - " << img << std::endl;
        textures.push_back(texture);
    } else {
        std::cout << "ERROR::Model::Texture : Failed to load texture - "<< img << std::endl;
    }
    stbi_image_free(data);
}
void Textures::useTexture(unsigned int index) {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, textures[index]);
};
void Textures::useAllTextures() {
    for (size_t i = 0; i < textures.size(); i++) {
        useTexture(i);
    }
};