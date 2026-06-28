#pragma once
#include "Core.h"
#include <glm/glm.hpp>
#include <random>
#include "Renderer/Renderer.h"
#include "Transform.h"
#include "Renderer/Primitives.h"

namespace Gameplay
{
	class AmmoCache : public Primitives::Square
	{
	public:
		AmmoCache();
		~AmmoCache();

		void OnInit();
		void OnUpdate(float dt);
		void OnRender();

		glm::vec3& GetPosition() { return transform.position; }
		Transform::Transform& GetTransform() { return transform; }
		bool IsOutofBounds() const { return outofBounds; }

	private:
		Transform::Transform transform;
		glm::vec3 direction;
		glm::vec3 target;

		bool outofBounds = false;

		int posbounds = 6, negbounds = -6;
		float speed = 2.0f;
	};
}