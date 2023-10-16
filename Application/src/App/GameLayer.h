#pragma once
#include "Core/Layer.h"
#include "Renderer/Renderer.h"
#include "Event/WindowEvent.h"

namespace Application
{
	class GameLayer : public Layer
	{
	private:
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnGuiRender() override;
		virtual void OnEvent(Event& e) override;

		bool OnWindowResize(WindowResizedEvent& e);

		Renderer* renderer;
	};
}