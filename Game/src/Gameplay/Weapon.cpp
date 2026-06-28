#include "gepch.h"
#include "Weapon.h"

Gameplay::Weapon::Weapon(const glm::vec3& playerposition, const glm::vec3& target)
	: speed(15.0f), target(0.0f, 0.0f, 0.0f), direction(0.0f, 0.0f, 0.0f),
	transform(Transform::Transform())
{

}

Gameplay::Weapon::Weapon()
	:speed(5.0f), target(0.0f, 0.0f, 0.0f), direction(0.0f, 0.0f, 0.0f),
	isActive(false),
	transform(Transform::Transform())
{
	transform.scalar = 0.35f;

}

Gameplay::Weapon::~Weapon()
{

}

void Gameplay::Weapon::OnInit(const glm::vec3& position, const glm::vec3& target)
{
	this->transform.position = position;
	this->target = target;

	this->direction = this->target - this->transform.position;
	this->direction = glm::normalize(direction);
	this->transform.rotationAngle = -atan2f(direction.y, direction.x) + glm::half_pi<float>();
}

void Gameplay::Weapon::OnUpdate(float dt)
{
	//std::cout << "direction: " << direction.x << ", " << direction.y << std::endl;
	this->transform.position += this->direction * dt * speed;
}

void Gameplay::Weapon::OnRender()
{
	Engine::Renderer::DrawWeaponTriangle(this->transform.position, this->transform.rotationAngle, this->transform.scalar);
}
