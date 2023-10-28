#include "GameLayer.h"
#include "Debugging/Logger.h"
#include "Core/Application.h"
#include <imgui.h>

namespace Application
{
	void GameLayer::OnAttach()
	{
		//on load
		renderer = Renderer::Create();
		model = new Model();
	}

	void GameLayer::OnDetach()
	{
		//on unload
		delete renderer;
		delete model;
	}

	void GameLayer::OnUpdate()
	{
		//game logic - update for every frames
		renderer->Clear();
		renderer->DrawElements(model->GetVertexArray(), model->GetShaders());
		//renderer->DrawArrays(model->GetVertexArray(), model->GetShaders());
	}

	void GameLayer::OnGuiRender()
	{
		//UI elements render
		//Application& app = Application::Get();

		//ImGui::Begin("Game", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		//ImGui::SetWindowPos(ImVec2(0, 0));
		//ImGui::SetWindowSize(ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight()));
		//ImGui::Button("Start game");
		//ImGui::Button("Settings game");
		//ImGui::Button("Exit game");
		//ImGui::End();
	}

	void GameLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizedEvent>(std::bind(&GameLayer::OnWindowResize, this, std::placeholders::_1));
	}

	bool GameLayer::OnWindowResize(WindowResizedEvent& e)
	{
		renderer->OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}