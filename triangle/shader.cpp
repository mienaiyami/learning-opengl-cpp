#include "shader.h"
#include "renderer.h"

Shader::Shader(const char* vertexpath, const char* fragmentpath) {
	std::string vertexcode;
	std::string fragmentcode;
	std::ifstream vertexshaderfile;
	std::ifstream fragmentshaderfile;
	//
	vertexshaderfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentshaderfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vertexshaderfile.open(vertexpath);
		fragmentshaderfile.open(fragmentpath);
		//
		std::stringstream vertexshaderstream, fragmentshaderstream;
		vertexshaderstream << vertexshaderfile.rdbuf();
		fragmentshaderstream << fragmentshaderfile.rdbuf();
		//
		vertexshaderfile.close();
		fragmentshaderfile.close();
		//
		vertexcode = vertexshaderstream.str();
		fragmentcode = fragmentshaderstream.str();
	}
	catch (std::ifstream::failure e) {
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}
	const char* vertexshadercode = vertexcode.c_str();
	const char* fragmentshadercode = fragmentcode.c_str();
	//
	unsigned int vertexshader, fragmentshader;
	//compile vertex shader
	vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexshadercode, NULL);
	glCompileShader(vertexshader);
	//compile fragment shader
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentshadercode, NULL);
	glCompileShader(fragmentshader);
	//vertex shader and fragment shader compilation status check and error printing
	checkcompilationstatus(vertexshader, "VERTEX");
	checkcompilationstatus(fragmentshader, "FRAGMENT");
	//program shader
	ID = glCreateProgram();
	glAttachShader(ID, vertexshader);
	glAttachShader(ID, fragmentshader);
	glLinkProgram(ID);
	//program shader linking status check and error printing
	checklinkingstatus(ID, "PROGRAM");
	//delete used shaders
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
}
Shader::~Shader() {
	glDeleteProgram(ID);
}

void Shader::use() const {
	GlCall(glUseProgram(ID));
}

void Shader::SetBool(const std::string& name, bool value) const {
	GlCall(glUniform1i(glGetUniformLocation(ID, name.c_str()), int(value)));
}
void Shader::SetInt(const std::string name, int value) const {
	GlCall(glUniform1i(glGetUniformLocation(ID, name.c_str()), value));
}
void Shader::SetFloat(const std::string name, float value) const {
	GlCall(glUniform1f(glGetUniformLocation(ID, name.c_str()), value));
}
// ------------------------------------------------------------------------
void Shader::SetVec2(const std::string& name, const glm::vec2& value) const {
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::SetVec2(const std::string& name, float x, float y) const {
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::SetVec3(const std::string& name, const glm::vec3& value) const {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::SetVec3(const std::string& name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::SetVec4(const std::string& name, const glm::vec4& value) const {
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const {
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const {
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const {
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::checkcompilationstatus(GLuint shader, std::string shadertype) const {
	int success;
	char infoLog[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << shadertype << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::checklinkingstatus(GLuint program, std::string shadertype) const {
	int success;
	char infoLog[1024];
	glGetShaderiv(program, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(program, 1024, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << shadertype << "::LINKING_FAILED\n" << infoLog << std::endl;
	}
}