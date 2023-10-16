#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
#include "ImGuiLayer.h"
#include "Core/Application.h"
#include "Core/KeyCodes.h"
#include "Renderer/Time.h"
#include <iostream>

namespace Application
{
	ImGuiLayer::ImGuiLayer()
	{
		OnAttach();
	}

	ImGuiLayer::~ImGuiLayer()
	{
		OnDetach();
	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		SetStyle();
		SetKeyMap();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors | ImGuiBackendFlags_HasSetMousePos;

		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		ImGui_ImplOpenGL3_Init("#version 460");

		//Begin();
		//SetDockSpace();
		//End();
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGui::GetIO().DeltaTime = Time::deltaTime;
	}

	void ImGuiLayer::Begin()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		//ImGui::SetNextWindowPos(ImGui::GetMainViewport()->WorkPos);
		//ImGui::SetNextWindowSize(ImGui::GetMainViewport()->WorkSize);
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
		//ImGui::Begin("Docking window", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus |
		//	ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNavFocus);
		//dockspaceId = ImGui::GetID("Docking window");
		//ImGui::DockSpace(dockspaceId, ImVec2(0, 0));
		//ImGui::End();
		//ImGui::PopStyleVar();
	}

	void ImGuiLayer::End()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		ImGui::EndFrame();
	}

	void ImGuiLayer::SetDockSpace()
	{
		ImGui::DockBuilderRemoveNode(dockspaceId);
		ImGui::DockBuilderAddNode(dockspaceId);
		ImGui::DockBuilderSetNodePos(dockspaceId, ImGui::GetMainViewport()->WorkPos);
		ImGui::DockBuilderSetNodeSize(dockspaceId, ImGui::GetMainViewport()->WorkSize);

		//dock window here

		ImGui::DockBuilderFinish(dockspaceId);
	}

	void ImGuiLayer::SetStyle() const
	{
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
		io.ConfigWindowsMoveFromTitleBarOnly = true;

		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.WindowPadding = ImVec2(5.0f, 5.0f);
			style.PopupRounding = 1.0f;
			style.FrameBorderSize = 0.0f;
			style.WindowMinSize.x = 240.0f;
			style.PopupBorderSize = 0.0f;
			style.FrameRounding = 1.0f;
			io.FontDefault = io.Fonts->AddFontFromFileTTF("Resources/Fonts/Open Sans/OpenSans-Regular.ttf", 18.0f);

			style.Colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };
			style.Colors[ImGuiCol_PopupBg] = ImVec4{ 0.25, 0.2505f, 0.251f, 1.0f };

			style.Colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
			style.Colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
			style.Colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

			style.Colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
			style.Colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

			style.Colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
			style.Colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
			style.Colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

			style.Colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
			style.Colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
			style.Colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
			style.Colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
			style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

			style.Colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
			style.Colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
			style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
		}
	}

	void ImGuiLayer::SetKeyMap() const
	{
		ImGuiIO& io = ImGui::GetIO();

		io.KeyMap[ImGuiKey_None] = KEY_UNKNOWN;
		io.KeyMap[ImGuiKey_Space] = KEY_SPACE;
		io.KeyMap[ImGuiKey_Backspace] = KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Tab] = KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = KEY_UP;
		io.KeyMap[ImGuiKey_PageUp] = KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = KEY_HOME;
		io.KeyMap[ImGuiKey_End] = KEY_END;
		io.KeyMap[ImGuiKey_Insert] = KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = KEY_DELETE;
		io.KeyMap[ImGuiKey_Enter] = KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = KEY_ESCAPE;
		io.KeyMap[ImGuiKey_LeftAlt] = KEY_LEFT_ALT;
		io.KeyMap[ImGuiKey_RightAlt] = KEY_RIGHT_ALT;
		io.KeyMap[ImGuiKey_LeftCtrl] = KEY_LEFT_CONTROL;
		io.KeyMap[ImGuiKey_RightCtrl] = KEY_RIGHT_CONTROL;
		io.KeyMap[ImGuiKey_LeftSuper] = KEY_LEFT_SUPER;
		io.KeyMap[ImGuiKey_RightSuper] = KEY_RIGHT_SUPER;
		io.KeyMap[ImGuiKey_LeftShift] = KEY_LEFT_SHIFT;
		io.KeyMap[ImGuiKey_RightShift] = KEY_RIGHT_SHIFT;
		io.KeyMap[ImGuiKey_0] = KEY_0;
		io.KeyMap[ImGuiKey_1] = KEY_1;
		io.KeyMap[ImGuiKey_2] = KEY_2;
		io.KeyMap[ImGuiKey_3] = KEY_3;
		io.KeyMap[ImGuiKey_4] = KEY_4;
		io.KeyMap[ImGuiKey_5] = KEY_5;
		io.KeyMap[ImGuiKey_6] = KEY_6;
		io.KeyMap[ImGuiKey_7] = KEY_7;
		io.KeyMap[ImGuiKey_8] = KEY_8;
		io.KeyMap[ImGuiKey_9] = KEY_9;
		io.KeyMap[ImGuiKey_A] = KEY_A;
		io.KeyMap[ImGuiKey_B] = KEY_B;
		io.KeyMap[ImGuiKey_C] = KEY_C;
		io.KeyMap[ImGuiKey_D] = KEY_D;
		io.KeyMap[ImGuiKey_E] = KEY_E;
		io.KeyMap[ImGuiKey_F] = KEY_F;
		io.KeyMap[ImGuiKey_G] = KEY_G;
		io.KeyMap[ImGuiKey_H] = KEY_H;
		io.KeyMap[ImGuiKey_I] = KEY_I;
		io.KeyMap[ImGuiKey_J] = KEY_J;
		io.KeyMap[ImGuiKey_K] = KEY_K;
		io.KeyMap[ImGuiKey_L] = KEY_L;
		io.KeyMap[ImGuiKey_M] = KEY_M;
		io.KeyMap[ImGuiKey_N] = KEY_N;
		io.KeyMap[ImGuiKey_O] = KEY_O;
		io.KeyMap[ImGuiKey_P] = KEY_P;
		io.KeyMap[ImGuiKey_Q] = KEY_Q;
		io.KeyMap[ImGuiKey_R] = KEY_R;
		io.KeyMap[ImGuiKey_S] = KEY_S;
		io.KeyMap[ImGuiKey_T] = KEY_T;
		io.KeyMap[ImGuiKey_U] = KEY_U;
		io.KeyMap[ImGuiKey_V] = KEY_V;
		io.KeyMap[ImGuiKey_W] = KEY_W;
		io.KeyMap[ImGuiKey_X] = KEY_X;
		io.KeyMap[ImGuiKey_Y] = KEY_Y;
		io.KeyMap[ImGuiKey_Z] = KEY_Z;
		io.KeyMap[ImGuiKey_F1] = KEY_F1;
		io.KeyMap[ImGuiKey_F2] = KEY_F2;
		io.KeyMap[ImGuiKey_F3] = KEY_F3;
		io.KeyMap[ImGuiKey_F4] = KEY_F4;
		io.KeyMap[ImGuiKey_F5] = KEY_F5;
		io.KeyMap[ImGuiKey_F6] = KEY_F6;
		io.KeyMap[ImGuiKey_F7] = KEY_F7;
		io.KeyMap[ImGuiKey_F8] = KEY_F8;
		io.KeyMap[ImGuiKey_F9] = KEY_F9;
		io.KeyMap[ImGuiKey_F10] = KEY_F10;
		io.KeyMap[ImGuiKey_F11] = KEY_F11;
		io.KeyMap[ImGuiKey_F12] = KEY_F12;
		io.KeyMap[ImGuiKey_Apostrophe] = KEY_APOSTROPHE;
		io.KeyMap[ImGuiKey_Comma] = KEY_COMMA;
		io.KeyMap[ImGuiKey_Minus] = KEY_MINUS;
		io.KeyMap[ImGuiKey_Period] = KEY_PERIOD;
		io.KeyMap[ImGuiKey_Slash] = KEY_SLASH;
		io.KeyMap[ImGuiKey_Semicolon] = KEY_SEMICOLON;
		io.KeyMap[ImGuiKey_Equal] = KEY_EQUAL;
		io.KeyMap[ImGuiKey_LeftBracket] = KEY_LEFT_BRACKET;
		io.KeyMap[ImGuiKey_Backslash] = KEY_BACKSLASH;
		io.KeyMap[ImGuiKey_RightBracket] = KEY_RIGHT_BRACKET;
		io.KeyMap[ImGuiKey_GraveAccent] = KEY_GRAVE_ACCENT;
		io.KeyMap[ImGuiKey_CapsLock] = KEY_CAPS_LOCK;
		io.KeyMap[ImGuiKey_ScrollLock] = KEY_SCROLL_LOCK;
		io.KeyMap[ImGuiKey_NumLock] = KEY_NUM_LOCK;
		io.KeyMap[ImGuiKey_PrintScreen] = KEY_PRINT_SCREEN;
		io.KeyMap[ImGuiKey_Pause] = KEY_PAUSE;
		io.KeyMap[ImGuiKey_ScrollLock] = KEY_SCROLL_LOCK;
		io.KeyMap[ImGuiKey_Menu] = KEY_MENU;
		io.KeyMap[ImGuiKey_Keypad0] = KEY_KP_0;
		io.KeyMap[ImGuiKey_Keypad1] = KEY_KP_1;
		io.KeyMap[ImGuiKey_Keypad2] = KEY_KP_2;
		io.KeyMap[ImGuiKey_Keypad3] = KEY_KP_3;
		io.KeyMap[ImGuiKey_Keypad4] = KEY_KP_4;
		io.KeyMap[ImGuiKey_Keypad5] = KEY_KP_5;
		io.KeyMap[ImGuiKey_Keypad6] = KEY_KP_6;
		io.KeyMap[ImGuiKey_Keypad7] = KEY_KP_7;
		io.KeyMap[ImGuiKey_Keypad8] = KEY_KP_8;
		io.KeyMap[ImGuiKey_Keypad9] = KEY_KP_9;
		io.KeyMap[ImGuiKey_KeypadDecimal] = KEY_KP_DECIMAL;
		io.KeyMap[ImGuiKey_KeypadDivide] = KEY_KP_DIVIDE;
		io.KeyMap[ImGuiKey_KeypadMultiply] = KEY_KP_MULTIPLY;
		io.KeyMap[ImGuiKey_KeypadSubtract] = KEY_KP_SUBTRACT;
		io.KeyMap[ImGuiKey_KeypadAdd] = KEY_KP_ADD;
		io.KeyMap[ImGuiKey_KeypadEnter] = KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_KeypadEqual] = KEY_KP_EQUAL;
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&ImGuiLayer::OnMouseButtonPressedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&ImGuiLayer::OnMouseButtonReleasedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseMovedEvent>(std::bind(&ImGuiLayer::OnMouseMovedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&ImGuiLayer::OnMouseScrolledEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyPressedEvent>(std::bind(&ImGuiLayer::OnKeyPressedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&ImGuiLayer::OnKeyReleasedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyTypedEvent>(std::bind(&ImGuiLayer::OnKeyTypeEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizedEvent>(std::bind(&ImGuiLayer::OnWindowResized, this, std::placeholders::_1));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;
		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;
		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());
		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel = e.GetYScroll();
		io.MouseWheelH = e.GetXScroll();
		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyTypeEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keyChar = e.GetKeyCode();
		io.AddInputCharacter(keyChar);
		return false;
	}

	bool ImGuiLayer::OnWindowResized(WindowResizedEvent& e)
	{
		Application& app = Application::Get();
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
		return false;
	}
}