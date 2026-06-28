#pragma once
#include "glm/glm.hpp"

struct GLFWwindow;

struct GLFWwindow;

namespace Tools
{
	class Utilities
	{
	public:
		Utilities() = default;
		~Utilities() = default;

		static glm::vec2 GetMouseWorldPos(GLFWwindow* window);
	};
}

