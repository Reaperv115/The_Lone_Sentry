#include "gepch.h"
#include "AmmoCache.h"

static thread_local std::mt19937 rng(std::random_device{}());

Gameplay::AmmoCache::AmmoCache()
	: transform(Transform::Transform())
{
	OnInit();
	//std::cout << "Ammo Cache spawned at: " << this->transform.position.x << ", " << this->transform.position.y << std::endl;
}

Gameplay::AmmoCache::~AmmoCache()
{

}

void Gameplay::AmmoCache::OnInit()
{
	this->transform.scalar = 1.0f;
	std::uniform_int_distribution<int> dist(negbounds, posbounds);


	this->transform.position = glm::vec3(negbounds, dist(rng), 0.0f);

	this->direction = glm::vec3(1.0f, 0.0f, 0.0f);
}

void Gameplay::AmmoCache::OnUpdate(float dt)
{
	this->transform.position += direction * dt * speed;
	
	if (this->transform.position.x > posbounds)
		outofBounds = true;
}

void Gameplay::AmmoCache::OnRender()
{
	Engine::Renderer::DrawSquare(this->transform.position, 0.0f, this->transform.scalar);
}

