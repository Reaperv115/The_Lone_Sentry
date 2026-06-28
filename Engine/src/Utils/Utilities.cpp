#include "gepch.h"
#include "Utilities.h"

glm::vec2 Tools::Utilities::GetMouseWorldPos(GLFWwindow* window)
{
	double mx, my;
	int width, height;
	glfwGetCursorPos(window, &mx, &my);
	glfwGetWindowSize(window, &width, &height);

	// Normalize to [-1, 1] range to match ortho projection
	float x = (float)(mx / width) * 2.0f - 1.0f;
	float y = 1.0f - (float)(my / height) * 2.0f; // flip y

	return { x, y };
}