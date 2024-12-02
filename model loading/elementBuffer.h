#pragma once

class ElementBuffer {
private:
    unsigned int id;
    unsigned int count;
    bool dataSet = false;
    bool deleteOnDeath;

public:
    ElementBuffer();
    ElementBuffer(const unsigned int *data, unsigned int count, bool deleteOnDeath = true);
    ~ElementBuffer();
    void bind() const;
    void setData(const unsigned int *data, unsigned int count, bool deleteOnDeath = true);
    void unbind() const;
    unsigned int GetCount() const { return count; }
};