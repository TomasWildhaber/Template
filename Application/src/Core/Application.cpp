#include "Application.h"
#include "GUI/ImGuiLayer.h"
#include "Debugging/Memory.h"
#include <iostream>
#include <imgui.h>

#include "App/GameLayer.h"

namespace Application
{
	Application* Application::instance = nullptr;

	Application::Application()
	{
		window = Window::Create(1270, 720, "Game");
		instance = this;
		window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		layerStack = new LayerStack();
		GuiLayer = new ImGuiLayer();

		PushLayer(new GameLayer);

		window->ShowWindow();
	}

	Application::~Application()
	{
		delete layerStack;
		delete GuiLayer;
		delete window;
	}

	void Application::Run()
	{
		while (isRunning)
		{
			window->OnUpdate();
			GuiLayer->OnUpdate();

			if (!isMinimized)
			{
				for (Layer* layer : *layerStack)
					layer->OnUpdate();

				GuiLayer->Begin();
				for (Layer* layer : *layerStack)
					layer->OnGuiRender();
				GuiLayer->End();
			}

			window->OnRender();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack->PushLayer(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizedEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));

		GuiLayer->OnEvent(e);

		for (auto it = layerStack->end(); it != layerStack->begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowClosedEvent& e)
	{
		isRunning = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizedEvent& e)
	{
		isMinimized = e.GetWidth() == 0 || e.GetName() == 0 ? true : false;
		return false;
	}
}