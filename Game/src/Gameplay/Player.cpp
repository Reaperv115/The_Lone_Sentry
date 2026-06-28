#include "gepch.h"
#include "Player.h"


Gameplay::Player::Player()
	: transform(Transform::Transform()), shotLoaded(true)
{
	transform.scalar = 1.0f;
}

Gameplay::Player::~Player()
{

}

void Gameplay::Player::OnInit()
{
	transform.position = glm::vec3(0.0f, 0.0f, 0.0f);

	
}

void Gameplay::Player::OnUpdate(GLFWwindow* window)
{
	glm::vec2 mousePos = Tools::Utilities::GetMouseWorldPos(window);
	glm::vec3 target = glm::vec3(mousePos, 0.0f);
	glm::vec3 spritePos = this->transform.position;

	// calculate angle from sprite to mouse
	float dx = spritePos.x - mousePos.x;
	float dy = spritePos.y - mousePos.y;
	this->transform.rotationAngle = atan2f(dy, dx) + glm::half_pi<float>();

	if (Engine::Input::IsMouseButtonPressed(0))
	{
		loadout.ShootNormalShot(spritePos, target);
	}

	if (Engine::Input::IsMouseButtonPressed(1))
	{
		loadout.ShootPowerShot(spritePos, target);
	}
}

void Gameplay::Player::OnRender()
{
	Engine::Renderer::DrawTriangle(this->transform.position, this->transform.rotationAngle, this->transform.scalar);
	loadout.OnRender();
}
