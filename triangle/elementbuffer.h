#pragma once

class ElementBuffer {
public:
	ElementBuffer(const unsigned int* IndicesData, unsigned int Indicescount);
	~ElementBuffer();

	void bind() const;
	void Unbind() const;
	unsigned int GetCount() const { return count; }

private:
	unsigned int ID;
	unsigned int count;
};