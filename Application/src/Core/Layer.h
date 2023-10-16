#pragma once
#include "Event/Event.h"

namespace Application
{
	class Layer
	{
	public:
		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnGuiRender() {}
		virtual void OnEvent(Event& e) {}
	private:
		virtual void HandleGuiWindowResize() {}
	};
}