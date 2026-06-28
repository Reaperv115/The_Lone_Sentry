#include "gepch.h"
#include "ErrorLogging.h"

void ErrorLog::GetErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

bool ErrorLog::LogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")" << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}
