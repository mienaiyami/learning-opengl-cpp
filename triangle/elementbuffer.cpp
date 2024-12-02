#include "ElementBuffer.h"

#include "renderer.h"

ElementBuffer::ElementBuffer(const unsigned int* IndicesData, unsigned int IndicesCount)
	:count(IndicesCount)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	GlCall(glGenBuffers(1, &ID));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
	GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), IndicesData, GL_STATIC_DRAW));
}

ElementBuffer::~ElementBuffer()
{
	GlCall(glDeleteBuffers(1, &ID));
}

void ElementBuffer::bind() const
{
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
}

void ElementBuffer::Unbind() const
{
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
