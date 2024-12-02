#pragma once

class VertexBuffer {
public:
	VertexBuffer(const void* vertdata, int size);
	~VertexBuffer();

	void bind() const;
	void Unbind() const;

private:
	unsigned int ID;
};