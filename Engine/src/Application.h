#pragma once
#include "Graphics/Graphics.h"
#include "../../Game/src/Layers/GameLayer.h"
#include "../../Game/src/Layers/ImGuiLayer.h"
#include "Layers/LayerStack.h"
#include "GameWindow.h"
#include "Events/WindowEvent.h"
#include "Core.h"

namespace Engine
{
	class Application
	{
	public:
		Application();
		~Application();

		void OnInit();
		void Run();
		void OnEvent(Event& event);
	private:
		LayerStack layerStack;
		bool isRunning = true;

		Unique<GameWindow> gameWindow;
	};
}

