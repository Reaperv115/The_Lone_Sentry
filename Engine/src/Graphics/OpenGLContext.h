#pragma once

struct GLFWwindow;

namespace Engine
{
	class OpenGLContext
	{
	public:
		OpenGLContext(GLFWwindow* windowhandle);

		void Init();
		void SwapBuffers();

		
	private:
		GLFWwindow* _windowhandle;
	};
}

