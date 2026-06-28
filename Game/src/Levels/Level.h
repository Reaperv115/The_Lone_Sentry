#pragma once
#include "vendor/glm/glm.hpp"
#include "../Gameplay/Player.h"
#include "../Gameplay/AmmoCache.h"
#include "Collision/CollisionDetection.h"
#include "../Gameplay/Enemy.h"
#include "../Gameplay/Loadout.h"
#include "../Gameplay/GameManager.h"

struct GLFWwindow;

namespace Gameplay
{
	class Level
	{
	public:
		Level();
		~Level();

		void OnInit(GLFWwindow* window);
		void OnUpdate(float dt);
		void OnRender();

		Player& GetPlayer() { return player; }

	private:
		GLFWwindow* window;
		Player player;
		Loadout loadout;
		Engine::Unique<AmmoCache> ammoCache = nullptr;
		std::vector<Engine::Unique<Enemy>> enemies;

		float enemyspawnTimer, enemyspawntimerMax = 3.5f;
		float ammocacheTimer, ammocachetimerMax = 3.0f;
	};
}

