#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Engine
{
	class Camera
	{
	public:
		Camera();

		glm::mat4x4 GetModelViewProjectionMatrix(const glm::mat4x4 modelWorldmat);
	private:
		float fov2D = 5.0f;
		glm::mat4x4 viewMatrixM4x4, projectionmatrixM4x4;
		float aspect = 1920.0f / 1080.0f;
	};
}

