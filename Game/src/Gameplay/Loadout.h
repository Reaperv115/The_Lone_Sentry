#pragma once
#include "Core.h"
#include <vector>
#include "Weapon.h"
#include <print>
#include <iostream>

namespace Gameplay
{
	class Loadout
	{
	public:
		Loadout();
		~Loadout();

		void Reload(int numshots);
		void FullReload();
		void ShootPowerShot(glm::vec3& startingpos, glm::vec3& target);
		void ShootNormalShot(glm::vec3& startingpos, glm::vec3& target);
		void OnInit();
		void OnUpdate();
		void OnRender();
		bool IsEmpty() const { return numpowerShots <= 0; }

		int GetAmmo() const { return numpowerShots; }
		inline void NormalShotCollided() { normalshotcollisionDetected = true; }
		inline void PowerShotCollided() { powershotcollisionDetected = true; }
		std::vector<Engine::Unique<Weapon>>& GetNormalShots() { return normalshots; }
		std::vector<Engine::Unique<Weapon>>& GetPowerShots() { return powershots; }


	private:

		std::vector<Engine::Unique<Weapon>> powershots;
		std::vector<Engine::Unique<Weapon>> normalshots;
		
		bool outofBounds;
		bool normalshotcollisionDetected, powershotcollisionDetected;
		int numpowerShots, maxnumPowershots = 10;
		float reloadTime;
	};
}