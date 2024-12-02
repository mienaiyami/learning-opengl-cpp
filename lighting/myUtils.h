#pragma once

#include <glad/glad.h>
#include <iostream>
#include <string>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GlCall(x) Gl_Clear_Error(); x; ASSERT(Gl_ErrorLog_call(#x, __FILE__, __LINE__));

void Gl_Clear_Error();
bool Gl_ErrorLog_call(const char* function, const char* file, int line);