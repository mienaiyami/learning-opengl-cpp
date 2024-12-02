#include "texture.h"
#include <stb_image.h>
#include "renderer.h"

Texture::Texture(const std::string path, bool isPng)
	:ID{ 0 }, FilePath{ path }, LocalBuffer{ nullptr },
	width{ 0 }, height{ 0 }, colorchannel{ 0 }
{
	GlCall(glGenTextures(1, &ID));
	GlCall(glBindTexture(GL_TEXTURE_2D, ID));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));

	//loading the image for texture
	if (!isPng) {
		LocalBuffer = stbi_load(path.c_str(), &width, &height, &colorchannel, 3);
		if (LocalBuffer) {
			GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, LocalBuffer));
			GlCall(glGenerateMipmap(GL_TEXTURE_2D));
		}
		else std::cout << path << " failed to load in texture" << std::endl;
	}
	else {
		stbi_set_flip_vertically_on_load(true);
		LocalBuffer = stbi_load(path.c_str(), &width, &height, &colorchannel, 4);
		if (LocalBuffer) {
			GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LocalBuffer));
			GlCall(glGenerateMipmap(GL_TEXTURE_2D));
		}
		else std::cout << path << " failed to load in texture" << std::endl;
	}
	if (LocalBuffer)
		stbi_image_free(LocalBuffer);
	GlCall(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::~Texture()
{
	GlCall(glDeleteTextures(1, &ID));
}

void Texture::bind(unsigned int slot) const
{
	GlCall(glActiveTexture(GL_TEXTURE0 + slot));
	GlCall(glBindTexture(GL_TEXTURE_2D, ID));
}

void Texture::Unbind() const
{
	GlCall(glBindTexture(GL_TEXTURE_2D, 0));
}

