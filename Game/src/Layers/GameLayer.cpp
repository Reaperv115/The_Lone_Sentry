#include "gepch.h"
#include "Gamelayer.h"


Gameplay::GameLayer::GameLayer(GLFWwindow* window)
	: window(window)
{
}

void Gameplay::GameLayer::OnAttach()
{
	level.OnInit(window);
}

void Gameplay::GameLayer::OnInit()
{
	//level.OnInit(window);
}

void Gameplay::GameLayer::OnUpdate(float dt)
{
	level.OnUpdate(dt);
}

void Gameplay::GameLayer::OnRender()
{
	level.OnRender();
}
