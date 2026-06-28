#include "gepch.h"
#include "Level.h"

Gameplay::Level::Level()
	:enemyspawnTimer(enemyspawntimerMax), ammocacheTimer(3.0f)
{

}

Gameplay::Level::~Level()
{

}

void Gameplay::Level::OnInit(GLFWwindow* window)
{
	this->window = window;
	player.OnInit();
	player.GetLoadout().OnInit();

	enemies.push_back(Engine::CreateUnique<Enemy>());
	ammoCache = Engine::CreateUnique<AmmoCache>();
}

void Gameplay::Level::OnUpdate(float dt)
{
	player.OnUpdate(window);
	for (auto& enemy : enemies)
		enemy->OnUpdate(dt);

	for (auto& powershot : player.GetLoadout().GetPowerShots())
		if (powershot->GetIsActive())
			powershot->OnUpdate(dt);

	for (auto& normalshot : player.GetLoadout().GetNormalShots())
		if (normalshot->GetIsActive())
			normalshot->OnUpdate(dt);

	if (ammoCache)
		ammoCache->OnUpdate(dt);


	if (enemyspawnTimer <= 0.0f)
	{
		enemies.push_back(Engine::CreateUnique<Enemy>());
		enemyspawnTimer = enemyspawntimerMax;
	}
	else
		enemyspawnTimer -= dt;

	if (ammocacheTimer <= 0.0f)
	{
		if (!ammoCache)
		{
			ammoCache = Engine::CreateUnique<AmmoCache>();
		}
		else if (!ammoCache->IsOutofBounds())
		{
			if (ammoCache->IsOutofBounds())
			{
				std::cout << ammocacheTimer << std::endl;
				ammocacheTimer -= dt;
				if (ammocacheTimer <= 0.0f)
				{
					ammoCache = Engine::CreateUnique<AmmoCache>();
					ammocacheTimer = ammocachetimerMax;
				}
			}
		}
	}

	// check for collisions between player and enemies
	for (auto it = enemies.begin(); it != enemies.end();)
	{
		float playerradius = player.GetRadius() * player.GetTransform().scalar;
		float enemyradius = (*it)->GetRadius() * (*it)->GetTransform().scalar;
		if (Engine::CollisionDetection::CheckCollision(
			player.GetPosition(),
			(*it)->GetPosition(),
			playerradius,
			enemyradius))
		{
			std::println("player hit");
			it = enemies.erase(it);
		}
		else
			++it;

	}

	// check for collisions between powershot and enemy
	for (auto& powershot : player.GetLoadout().GetPowerShots())
	{
		if (!powershot->GetIsActive())
			continue;
		else
		{
			for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();)
			{
				float powershotradius = powershot->GetRadius() * powershot->GetTransform().scalar;
				float enemyradius = (*enemyIt)->GetRadius() * (*enemyIt)->GetTransform().scalar;
				if (Engine::CollisionDetection::CheckCollision(
					powershot->GetPosition(),
					(*enemyIt)->GetPosition(),
					powershotradius,
					enemyradius))
				{
					std::println("enemy hit");
					powershot->SetIsActive(false);
					enemyIt = enemies.erase(enemyIt);
				}
				else
					++enemyIt;
			}
		}
	}

	for (auto& powershot : player.GetLoadout().GetPowerShots())
	{
		if (powershot->GetIsActive() && ammoCache)
		{
			if (!ammoCache->IsOutofBounds())
			{
				float weaponradius = powershot->GetRadius() * powershot->GetTransform().scalar;
				float ammocacheradius = ammoCache->GetRadius() * ammoCache->GetTransform().scalar;
				if (Engine::CollisionDetection::CheckCollision(powershot->GetPosition(),
					ammoCache->GetPosition(),
					weaponradius,
					ammocacheradius))
				{
					std::println("ammo cache hit");
					ammoCache = nullptr;
				}
			}

		}
	}


	// normal shot collision with enemies
	for (auto enemyit = enemies.begin(); enemyit != enemies.end();)
	{
		bool erased = false;
		for (auto weaponit = player.GetLoadout().GetNormalShots().begin(); weaponit != player.GetLoadout().GetNormalShots().end(); ++weaponit)
		{
			if ((*weaponit)->GetIsActive())
			{
				float weaponradius = (*weaponit)->GetRadius() * (*weaponit)->GetTransform().scalar;
				float enemyradius = (*enemyit)->GetRadius() * (*enemyit)->GetTransform().scalar;
				if (Engine::CollisionDetection::CheckCollision(
					(*weaponit)->GetPosition(),
					(*enemyit)->GetPosition(),
					weaponradius,
					enemyradius))
				{
					std::println("enemy hit");
					player.GetLoadout().NormalShotCollided();
					enemyit = enemies.erase(enemyit);
					erased = true;
					GameManager::GetInstance().IncrementScore();
					break;
				}
			}
		}
		if (!erased)
			++enemyit;
	}


	// normal shot collision with ammo cache
	for (auto weaponit = player.GetLoadout().GetNormalShots().begin(); weaponit != player.GetLoadout().GetNormalShots().end(); ++weaponit)
	{
		if ((*weaponit)->GetIsActive() && ammoCache)
		{
			if (!ammoCache->IsOutofBounds())
			{
				float weaponradius = (*weaponit)->GetRadius() * (*weaponit)->GetTransform().scalar;
				float ammocacheradius = ammoCache->GetRadius() * ammoCache->GetTransform().scalar;
				if (Engine::CollisionDetection::CheckCollision((*weaponit)->GetPosition(),
					ammoCache->GetPosition(),
					weaponradius,
					ammocacheradius))
				{
					std::println("ammo cache hit");
					ammoCache = nullptr;
				}
			}

		}
	}

	player.GetLoadout().OnUpdate();

}

void Gameplay::Level::OnRender()
{
	player.OnRender();
	for (auto& normalshot : player.GetLoadout().GetNormalShots())
		if (normalshot->GetIsActive())
			normalshot->OnRender();
	for (auto& powerrshot : player.GetLoadout().GetPowerShots())
		if (powerrshot->GetIsActive())
			powerrshot->OnRender();
	if (ammoCache)
		ammoCache->OnRender();
	for (auto& enemy : enemies)
		enemy->OnRender();
}
