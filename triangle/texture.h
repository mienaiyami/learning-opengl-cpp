#pragma once

#include <glad/glad.h>

#include <iostream>
#include <string>

class Texture {
public:
	Texture(const std::string path, bool isPng);
	~Texture();

	void bind(unsigned int slot) const;
	void Unbind() const;

private:
	unsigned int ID;
	std::string FilePath;
	unsigned char* LocalBuffer;
	int width, height, colorchannel;
};
