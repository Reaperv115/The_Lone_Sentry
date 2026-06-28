#include "Loadout.h"

namespace Gameplay
{

	Loadout::Loadout()
		: numpowerShots(10), reloadTime(1.0f), normalshotcollisionDetected(false), powershotcollisionDetected(false)
	{
		
	}

	Loadout::~Loadout()
	{

	}

	void Loadout::OnInit()
	{
		for (int i = 0; i < maxnumPowershots; ++i)
		{
			powershots.push_back(Engine::CreateUnique<Weapon>());
		}
	}

	void Loadout::Reload(int numshots)
	{
		for (int i = 0; i < numshots; ++i)
		{
			powershots.push_back(Engine::CreateUnique<Weapon>());
		}
	}

	void Loadout::FullReload()
	{
		int numpowershotsToAdd = maxnumPowershots - numpowerShots;
		for (int i = 0; i < numpowershotsToAdd; ++i)
		{
			powershots.push_back(Engine::CreateUnique<Weapon>());
		}
	}

	void Loadout::ShootPowerShot(glm::vec3& startingpos, glm::vec3& target)
	{
		if (IsEmpty())
		{
			std::println("Out of ammo!");
			return;
		}
		else
		{
			for (auto& missile : powershots)
			{
				if (!missile->GetIsActive())
				{
					missile->OnInit(startingpos, target);
					missile->SetIsActive(true);
					--numpowerShots;
					std::cout << "Shot fired! Remaining ammo: " << numpowerShots << std::endl;
					break;
				}
			}
		}
	}

	void Loadout::ShootNormalShot(glm::vec3& startingpos, glm::vec3& target)
	{
		Engine::Unique<Weapon> normshot = Engine::CreateUnique<Weapon>();
		normshot->OnInit(startingpos, target);
		normshot->SetIsActive(true);
		normalshots.push_back(std::move(normshot));
	}

	

	void Loadout::OnUpdate()
	{
		for (auto& powershot : powershots)
		{
			if  ((powershot)->GetIsActive())
			{
				if ((powershot)->GetPosition().x < -10.0f || (powershot)->GetPosition().x > 10.0f ||
					(powershot)->GetPosition().y < -10.0f || (powershot)->GetPosition().y > 10.0f)
				{
					outofBounds = true;
					break;
				}

				if (powershotcollisionDetected || outofBounds)
				{
					(powershot)->SetIsActive(false);
					powershotcollisionDetected = false;
					outofBounds = false;
					break;
				}
			}
		}

		for (auto& normshot : normalshots)
		{
			if (normshot->GetIsActive())
			{
				if (normshot->GetPosition().x < -10.0f || normshot->GetPosition().x > 10.0f ||
					normshot->GetPosition().y < -10.0f || normshot->GetPosition().y > 10.0f)
				{
					normshot->SetIsActive(false);
				}
				else if (normalshotcollisionDetected)
				{
					normshot->SetIsActive(false);
					normalshotcollisionDetected = false;
				}
			}
		}
	}

	void Loadout::OnRender()
	{
		for (auto& powershot : powershots)
		{
			if (powershot->GetIsActive())
				powershot->OnRender();
		}

		for (auto& normalshot : normalshots)
		{
			if (normalshot->GetIsActive())
				normalshot->OnRender();
		}
		
	}

}