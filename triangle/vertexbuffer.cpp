#include "vertexbuffer.h"

#include "renderer.h"

VertexBuffer::VertexBuffer(const void* vertdata, int size)
{
	GlCall(glGenBuffers(1, &ID));
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, ID));
	GlCall(glBufferData(GL_ARRAY_BUFFER, size, vertdata, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GlCall(glDeleteBuffers(1, &ID));
}

void VertexBuffer::bind() const
{
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, ID));
}

void VertexBuffer::Unbind() const
{
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
