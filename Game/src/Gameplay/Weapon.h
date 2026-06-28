#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/constants.hpp>
#include "Renderer/Renderer.h"
#include "Textures/Texture.h"
#include "Transform.h"
#include "Renderer/Primitives.h"

namespace Gameplay

{
	class Weapon : public Primitives::Triangle
	{
	public:
		Weapon(const glm::vec3& playerposition, const glm::vec3& target);
		Weapon();
		~Weapon();

		void OnInit(const glm::vec3& playerposition, const glm::vec3& target);
		void OnUpdate(float dt);
		void OnRender();
		inline void SetIsActive(bool active) { isActive = active; }
		inline bool GetIsActive() const { return isActive; }

		glm::vec3& GetPosition() { return transform.position; }
		Transform::Transform& GetTransform() { return transform; }

	private:
		float speed;
		bool isActive;
		glm::vec3 target;
		glm::vec3 direction;
		Transform::Transform transform;
	};
}