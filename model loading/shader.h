#pragma once

#include "glmInclude.h"
#include "myUtils.h"
#include <fstream>
#include <glad/glad.h>
#include <sstream>

class Shader {
public:
    unsigned int id;
    Shader(const char *vertexPath, const char *fragmentPath);
    ~Shader();
    void use() const;
    bool checkUniformExist(const std::string &name)const;
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, float x, float y, float z, float a) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;

private:
    void checkCompileErrors(unsigned int shader, std::string type);
};
