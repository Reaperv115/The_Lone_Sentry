#include "gepch.h"
#include "Application.h"

Engine::Application::Application()
{
	OnInit();
}

Engine::Application::~Application()
{

}

void Engine::Application::OnInit()
{
	gameWindow = CreateUnique<GameWindow>();
	gameWindow->SetEventCallback(GE_BIND_EVENT_FN(Engine::Application::OnEvent));

	auto gameLayer = CreateUnique<Gameplay::GameLayer>(gameWindow->GetGFX()->GetNativeWindow());
	Gameplay::GameLayer* gamelayer = gameLayer.get();
	layerStack.PushLayer(std::move(gameLayer));

	auto imguiLayer = CreateUnique<Gameplay::ImGuiLayer>(gameWindow->GetGFX()->GetNativeWindow(), gamelayer->GetLevel());
	layerStack.PushLayer(std::move(imguiLayer));

	Input::Initialize(gameWindow->GetGFX()->GetNativeWindow());
}

void Engine::Application::Run()
{
	float lasttime = (float)glfwGetTime();

	while (isRunning && !gameWindow->GetGFX()->ShouldWindowClose())
	{
		float currentTime = (float)glfwGetTime();
		float deltatime = currentTime - lasttime;
		lasttime = currentTime;
		if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
		{
			glfwSetInputMode(gameWindow->GetGFX()->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (auto& layer : layerStack)
		{
			layer->OnUpdate(deltatime);
			layer->OnRender();
		}
		gameWindow->OnUpdate();
	}
}

void Engine::Application::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e)
		{
			isRunning = false;
			return true;
		});

	for (auto it = layerStack.rbegin(); it != layerStack.rend(); ++it)
	{
		if (event.handled)
			break;
		(*it)->OnEvent(event);
	}
}
