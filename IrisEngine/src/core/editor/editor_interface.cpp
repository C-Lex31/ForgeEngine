#include "irpch.h"
#include "editor_interface.h"
//#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
namespace Iris {

	UI_Layer::UI_Layer()
		:Layer("Base_Layer")
	{

	}
	UI_Layer::~UI_Layer()
	{

	}
	void UI_Layer::OnAttach()
	{
		
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
		
	}
	void UI_Layer::OnDetach()
	{

	}
	void UI_Layer::OnUpdate()
	{
		ImGuiIO& iot = ImGui::GetIO();
		Application& is = Application::Get();
		iot.DisplaySize = ImVec2(is.GetWindow().GetWidth(), is.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		iot.DeltaTime = (m_Time > 0) ? time - m_Time : (1.0f / 60);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		

	}
	void UI_Layer::OnEvent(Event& event)
	{
		EventDispatcher disp(event);
		disp.Dispatch<MouseButtonPressedEvent>(IR_BIND_EVENT_FN(UI_Layer::OnMouseButtonPressedEvent));
		disp.Dispatch<MouseButtonReleasedEvent>(IR_BIND_EVENT_FN(UI_Layer::OnMouseButtonReleasedEvent));
		disp.Dispatch<MouseMovedEvent>(IR_BIND_EVENT_FN(UI_Layer::OnMouseMovedEvent));
		disp.Dispatch<MouseScrolledEvent>(IR_BIND_EVENT_FN(UI_Layer::OnMouseScrolledEvent));
		disp.Dispatch<KeyPressedEvent>(IR_BIND_EVENT_FN(UI_Layer::OnKeyPressedEvent));
		disp.Dispatch<KeyReleasedEvent>(IR_BIND_EVENT_FN(UI_Layer::OnKeyReleasedEvent));
		disp.Dispatch<WindowResizeEvent>(IR_BIND_EVENT_FN(UI_Layer::OnWindowResizeEvent));
	}

	bool UI_Layer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}
	bool UI_Layer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{

		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}
	bool UI_Layer::OnMouseMovedEvent(MouseMovedEvent& e)
	{

		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}
	bool UI_Layer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();
        
		return false;
	}
	bool UI_Layer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		return false;
	}
	bool UI_Layer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		return false;
	}
	bool UI_Layer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

		return false;
	}





}
