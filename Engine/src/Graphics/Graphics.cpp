#include "gepch.h"
#include "Graphics.h"

Engine::Graphics::Graphics(float width, float height, const std::string& windowname)
	:windowWidth(width), windowHeight(height), windowTitle(windowname)
{

}

void Engine::Graphics::InitializeGraphics()
{
	if (!glfwInit())
	{
		std::println("Failed to initialize GLFW");
		return;
	}

	_window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, NULL);
	if (!_window)
	{
		std::println("Failed to create window");
	}

	windowContext = CreateUnique<OpenGLContext>(_window);
	windowContext->Init();

	glViewport(0, 0, windowWidth, windowHeight);


	SetAPIFlags();
}

void Engine::Graphics::SetAPIFlags()
{
	Call(glEnable(GL_BLEND));
	Call(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	Call(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
	Call(glEnable(GL_DEPTH_TEST));
}

bool Engine::Graphics::ShouldWindowClose() const
{
	return glfwWindowShouldClose(_window);
}
