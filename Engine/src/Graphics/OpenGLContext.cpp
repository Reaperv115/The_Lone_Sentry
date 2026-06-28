#include "gepch.h"
#include "OpenGLContext.h"

Engine::OpenGLContext::OpenGLContext(GLFWwindow* windowhandle)
	:_windowhandle(windowhandle)
{

}

void Engine::OpenGLContext::Init()
{
	glfwMakeContextCurrent(_windowhandle);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::println("Failed to load glad");
	}
	glfwSwapInterval(1);
}

void Engine::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(_windowhandle);
}

