#pragma once
#include "Transform.h"
#include "glm/glm.hpp"
#include "Core.h"
#include <random>
#include "glm/gtc/constants.hpp"
#include "Renderer/Renderer.h"
#include"Renderer/Primitives.h"

namespace Gameplay
{
	class Enemy : public Primitives::Triangle
	{
	public:
		Enemy();
		~Enemy();

		void OnInit();
		void OnUpdate(float dt);
		void OnRender();

		Transform::Transform& GetTransform() { return transform; }
		glm::vec3& GetPosition() { return transform.position; }
	private:
		float speed = 0.5f;
		glm::vec3 target;
		float angle;
		Transform::Transform transform;
	};
}