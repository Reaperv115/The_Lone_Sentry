#include "gepch.h"
#include "GameWindow.h"

Engine::GameWindow::GameWindow(const GameWindowSettings& settings /*= GameWindowSettings()*/)
{
	OnInit(settings);
}

Engine::Unique<Engine::GameWindow> Engine::GameWindow::CreateGameWindow(const GameWindowSettings& settings /*= GameWindowSettings()*/)
{
	return CreateUnique<GameWindow>(settings);
}

void Engine::GameWindow::OnInit(const GameWindowSettings& settings)
{
	gfx = CreateUnique<Graphics>(settings.width, settings.height, "Game Engine");
	gfx->InitializeGraphics();

    Renderer::Init();

	glfwSetWindowUserPointer(gfx->GetNativeWindow(), &eventcallback);
	glfwSetInputMode(gfx->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	glfwSetWindowCloseCallback(gfx->GetNativeWindow(), [](GLFWwindow* window)
		{
			auto& callback = *static_cast<EventCallbackFn*>(glfwGetWindowUserPointer(window));
			WindowCloseEvent event;
			callback(event);
		});
	glfwSetWindowSizeCallback(gfx->GetNativeWindow(), [](GLFWwindow* window, int width, int height)
		{
			auto& callback = *static_cast<EventCallbackFn*>(glfwGetWindowUserPointer(window));
			WindowResizeEvent event(width, height);
			callback(event);
		});
	

	glfwSetWindowFocusCallback(gfx->GetNativeWindow(), [](GLFWwindow* w, int focused)
		{
			if (focused)
			{
				glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				if (glfwRawMouseMotionSupported()) glfwSetInputMode(w, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
			}
			else
			{
				glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				if (glfwRawMouseMotionSupported()) glfwSetInputMode(w, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
			}
		});

	/*glfwSetMouseButtonCallback(gfx->GetNativeWindow(), [](GLFWwindow* window, int button, int action, int mods)
		{
			auto& callback = *static_cast<EventCallbackFn*>(glfwGetWindowUserPointer(window));
			switch (action)
			{
			case GLFW_PRESS: { MouseButtonPressedEvent event(button); callback(event); break; }
			case GLFW_RELEASE: { MouseButtonReleasedEvent event(button); callback(event); break; }
			}
		});*/
}

void Engine::GameWindow::OnUpdate()
{
	Input::OnUpdate();
	glfwPollEvents();
	gfx->SwapBuffers();
}


