#pragma once
#include "Transform.h"
#include "Input/Input.h"
#include "Utils/Utilities.h"
#include "glm/gtc/constants.hpp"
#include "Renderer/Renderer.h"
#include "Loadout.h"
#include "Renderer/Primitives.h"


struct GLFWwindow;

namespace Gameplay
{
	class Player : public Primitives::Triangle
	{
	public:
		Player();
		~Player();

		void OnInit();
		void OnUpdate(GLFWwindow* window);
		void OnRender();

		inline bool IsShotLoaded() const { return shotLoaded; }
		const inline Transform::Transform& GetTransform() const { return transform; }
		const inline glm::vec3& GetPosition() const { return transform.position; }
		const inline Loadout& GetLoadout() const { return loadout; }
		inline Loadout& GetLoadout() { return loadout; }


	private:
		Loadout loadout;

		Transform::Transform transform;
		float radius;
		bool shotLoaded = true;
	};
}

