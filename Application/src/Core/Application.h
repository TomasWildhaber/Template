#pragma once
#include "Window.h"
#include "LayerStack.h"
#include "Event/WindowEvent.h"
#include "GUI/ImGuiLayer.h"

namespace Application
{
	class Application
	{
	public:
		Application();
		~Application();

		inline static Application& Get() { return *instance; }
		inline Window& GetWindow() { return *window; }

		void OnEvent(Event& e);
		void Run();

		inline ImGuiLayer& GetGuiLayer() { return *GuiLayer; }
		void PushLayer(Layer* layer);
	private:
		bool OnWindowClose(WindowClosedEvent& e);
		bool OnWindowResize(WindowResizedEvent& e);
		static Application* instance;

		Window* window;
		ImGuiLayer* GuiLayer;
		LayerStack* layerStack;
		bool isRunning = true;
		bool isMinimized = false;
	};
}