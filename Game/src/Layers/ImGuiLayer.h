#pragma once
#include "Layers/Layer.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "../Gameplay/GameManager.h"
#include "../Levels/Level.h"

struct GLFWwindow;

namespace Gameplay
{
	class ImGuiLayer : public Engine::Layer
	{
	public:
		ImGuiLayer(GLFWwindow* window, Level& level);
		~ImGuiLayer();

		void OnAttach() override;
		void OnUpdate(float dt);
		void OnRender() override;
	private:
		GLFWwindow* window;
		Level& level;
	};
}