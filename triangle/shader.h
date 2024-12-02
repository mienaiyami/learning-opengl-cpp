#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	Shader(const char* vertexpath, const char* fragmentpath);
	~Shader();

	//set uniform
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string name, int value) const;
	void SetFloat(const std::string name, float value) const;
	// ------------------------------------------------------------------------
	void SetVec2(const std::string& name, const glm::vec2& value) const;
	void SetVec2(const std::string& name, float x, float y) const;
	// ------------------------------------------------------------------------
	void SetVec3(const std::string& name, const glm::vec3& value) const;
	void SetVec3(const std::string& name, float x, float y, float z) const;
	// ------------------------------------------------------------------------
	void SetVec4(const std::string& name, const glm::vec4& value) const;
	void SetVec4(const std::string& name, float x, float y, float z, float w) const;
	// ------------------------------------------------------------------------
	void SetMat2(const std::string& name, const glm::mat2& mat) const;
	void SetMat3(const std::string& name, const glm::mat3& mat) const;
	void SetMat4(const std::string& name, const glm::mat4& mat) const;


	unsigned int getID() { return ID; }
	//useprogram and deleteprogram
	void use() const;
private:
	unsigned int ID;
	void checkcompilationstatus(GLuint shader, std::string shadertype) const;
	void checklinkingstatus(GLuint program, std::string shadertype) const;
};

#endif // !SHADER_H