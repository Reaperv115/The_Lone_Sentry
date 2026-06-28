#pragma once
#include "Layers/Layer.h"
#include "../Levels/Level.h"

struct GLFWwindow;

namespace Gameplay
{
	class GameLayer : public Engine::Layer
	{
	public:
		GameLayer(GLFWwindow* window);
		virtual ~GameLayer() = default;
		void OnAttach() override;

		void OnInit();
		void OnUpdate(float dt) override;
		void OnRender() override;

		Level& GetLevel() { return level; }

		Level level;

	private:
		GLFWwindow* window;
	};
}

