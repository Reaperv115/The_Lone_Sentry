#include "gepch.h"
#include "Camera.h"

Engine::Camera::Camera()
{
	viewMatrixM4x4 = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
	projectionmatrixM4x4 = glm::ortho(-aspect * fov2D, aspect * fov2D, -fov2D, fov2D, 0.1f, 1000.0f);
}

glm::mat4x4 Engine::Camera::GetModelViewProjectionMatrix(const glm::mat4x4 modelWorldmat)
{
	return projectionmatrixM4x4 * viewMatrixM4x4 * modelWorldmat;
}
