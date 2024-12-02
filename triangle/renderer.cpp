#include "renderer.h"
#include <iostream>
//#include "elementbuffer.h"

void Gl_Clear_Error() {
	while (glGetError());
}
bool Gl_ErrorLog_call(const char* function, const char* file, int line) {
	if (GLenum error = glGetError()) {
		std::cout << "OPENGL::ERROR::" << error << "::" << function << "\n" << file << "::" << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::draw(const unsigned int& VertexArrayObject, const ElementBuffer& ElementBufferObject, const Shader& shader)
{
	shader.use();
	GlCall(glBindVertexArray(VertexArrayObject));
	ElementBufferObject.bind();
	GlCall(glDrawElements(GL_TRIANGLES, ElementBufferObject.GetCount(), GL_UNSIGNED_INT, 0));

}

void Renderer::clear() const {
	glClearColor(0.1f, 0.125f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
