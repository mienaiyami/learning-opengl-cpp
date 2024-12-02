#include "shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    checkCompileErrors(id, "PROGRAM");
    glDeleteShader(vertex);
    glDeleteShader(fragment);
};
Shader::~Shader() {
    GlCall(glDeleteProgram(id));
    std::cout << "MESSAGE::Shader : Shader deleted " << id << std::endl;
}
void Shader::checkCompileErrors(unsigned int shader, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

void Shader::use() const {
    glUseProgram(id);
}

bool Shader::checkUniformExist(const std::string &name)const {
    if (glGetUniformLocation(id, name.c_str()) <= -1) {
        std::cout << "ERROR::SHADER::SetUniform : uniform " << name << " doesnt exist." << std::endl;
        return false;
    }
    return true;
}

//
//
//
//todo: check if use() on each method heavy
//
//
//

void Shader::setBool(const std::string &name, bool value) const {
    if(!checkUniformExist(name)) return;
    use();
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const {
    if(!checkUniformExist(name)) return;
    use();
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
    if(!checkUniformExist(name)) return;
    use();
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
    if(!checkUniformExist(name)) return;
    use();
    glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    if(!checkUniformExist(name)) return;
    use();
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const {
    if(!checkUniformExist(name)) return;
    use();
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float a) const {
    if(!checkUniformExist(name)) return;
    use();
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, a);
}
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
    if(!checkUniformExist(name)) return;
    use();
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::setMat4(const std::string &name, glm::mat4 value) const {
    if(!checkUniformExist(name)) return;
    use();
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}