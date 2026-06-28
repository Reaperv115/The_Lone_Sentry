#include "gepch.h"
#include "ImGuiLayer.h"

Gameplay::ImGuiLayer::ImGuiLayer(GLFWwindow* window, Level& _level)
	: window(window), level(_level)
{

}

Gameplay::ImGuiLayer::~ImGuiLayer()
{

}

void Gameplay::ImGuiLayer::OnAttach()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 450");
}

void Gameplay::ImGuiLayer::OnUpdate(float dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(1850.0f, 0.0f), ImGuiCond_Always);
	ImGui::Begin("Score:");
	ImGui::Text("Score: %d", Gameplay::GameManager::GetInstance().GetScore());
	ImGui::End();

	// TODO: ammo counter
	ImGui::SetNextWindowPos(ImVec2(1850.0f, 1030.0f), ImGuiCond_Always);
	ImGui::Begin("Ammo");
	ImGui::Text("Ammo: %d", level.GetPlayer().GetLoadout().GetAmmo(), ImGuiCond_Always);
	ImGui::End();
	//ImGui::Text("Power shots: ", )
}

void Gameplay::ImGuiLayer::OnRender()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
