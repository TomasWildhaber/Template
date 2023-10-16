#pragma once
#include "Core/Layer.h"
#include "Event/Events.h"

namespace Application
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();
	private:
		void SetStyle() const;
		void SetKeyMap() const;
		void SetDockSpace();

		uint32_t dockspaceId;
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypeEvent(KeyTypedEvent& e);
		bool OnWindowResized(WindowResizedEvent& e);
	};
}