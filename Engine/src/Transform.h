#pragma once
#include "glm/glm.hpp"

namespace Transform
{
	struct Transform
	{
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		float scalar = 1.0f;
		float rotationAngle = 0.0f;
	};
}