#pragma once
#include <string>
#include "Events/Event.h"

struct GLFWwindow;

namespace Engine
{
	class Layer
	{
	public:
		Layer(const std::string& debugname = "Layer") {}

		virtual void OnAttach(){}
		virtual void OnUpdate(float dt){}
		virtual void OnRender(){}
		virtual void OnEvent(Event& e){}
		virtual void OnImGuiRender(){}
		virtual void OnImGuiBegin(){}
		virtual void OnImGuiEnd(){}
		virtual void OnDetach(){}
	protected:
		std::string debugName;
	};
}
