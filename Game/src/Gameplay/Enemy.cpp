#include "gepch.h"
#include "Enemy.h"

static thread_local std::mt19937 rng(std::random_device{}());

Gameplay::Enemy::Enemy()
	: target(0.0f, 0.0f, 0.0f), transform(Transform::Transform())
{
	OnInit();
}

Gameplay::Enemy::~Enemy()
{

}

void Gameplay::Enemy::OnInit()
{
	int posbounds = 6, negbounds = -6;
	this->transform.scalar = 1.0f;
	std::uniform_int_distribution<int> dist(negbounds, posbounds);
	int x = dist(rng);
	int y;
	if (x == negbounds || x == posbounds)
	{
		y = dist(rng);
	}
	else
	{
		std::uniform_int_distribution<int> dist2(-4, 4);
		y = dist2(rng);
	}
	this->transform.position = glm::vec3(x, y, 0);
	float dx = this->transform.position.x - this->target.x;
	float dy = this->transform.position.y - this->target.y;

	this->transform.rotationAngle = atan2f(dy, dx) + glm::half_pi<float>();
}

void Gameplay::Enemy::OnUpdate(float dt)
{
	glm::vec3 direction = glm::normalize(this->target - this->transform.position);
	this->transform.position += speed * direction * dt;
}

void Gameplay::Enemy::OnRender()
{
	Engine::Renderer::DrawTriangle(this->transform.position, this->transform.rotationAngle, this->transform.scalar);
}
