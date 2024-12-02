#include "myUtils.h"

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
