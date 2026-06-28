#pragma once

// C++ macros for debugging opengl

namespace ErrorLog
{
	void GetErrors();

	bool LogCall(const char* function, const char* file, int line);
}
