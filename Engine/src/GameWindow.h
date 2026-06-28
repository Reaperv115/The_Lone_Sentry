#pragma once
#include "Core.h"
#include "Graphics/Graphics.h"
#include "Graphics/OpenGLContext.h"
#include <functional>
#include "Events/Event.h"
#include "Events/WindowEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseButtonEvent.h"
#include "Renderer/Renderer.h"
#include "Input/Input.h"


namespace Engine
{
	struct GameWindowSettings
	{
		float width = 1920;
		float height = 1080;
		std::string title = "Game Window";
	};

	using EventCallbackFn = std::function<void(Event&)>;

	class GameWindow
	{
	public:
		GameWindow(const GameWindowSettings& settings = GameWindowSettings());
		virtual ~GameWindow() = default;

		Unique<GameWindow> CreateGameWindow(const GameWindowSettings& settings = GameWindowSettings());
		inline Unique<Graphics>& GetGFX() { return gfx; }

		void OnInit(const GameWindowSettings& settings);
		void OnUpdate();
		void SetEventCallback(const EventCallbackFn& callback) { eventcallback = callback; }

		

	private:
		Unique<Graphics> gfx;
		Unique<Renderer> renderer;
		EventCallbackFn eventcallback;
	};
}

