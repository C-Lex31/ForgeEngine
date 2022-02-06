#include "frpch.h"
#include "editor_interface.h"
//#include <imgui.h>
#include "core/main/main.h"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glad/glad.h>
namespace Forge {

	UI_Layer::UI_Layer()
		:Layer("Base_Layer")
	{

	}
	
	void UI_Layer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ForgeUI::CreateContext();									//ImGui----->ForgeUI
		FListenIO& io = ForgeUI::GetIO(); (void)io;					//ImGuiIO--->FListenIO
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Gui style
		//ImGui::StyleColorsDark();
		ForgeUI::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		FStyle& style = ForgeUI::GetStyle();						//ImGuiStyle--->FStyle
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
		
	
		
	}
	void UI_Layer::OnDetach()
	{

	}
	void UI_Layer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ForgeUI::NewFrame();
	}
	void UI_Layer::End()
	{
		FListenIO& io = ForgeUI::GetIO();
		Application& is = Application::Get();
		io.DisplaySize = FVec2((float)is.GetWindow().GetWidth(), (float)is.GetWindow().GetHeight());

		ForgeUI::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ForgeUI::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ForgeUI::UpdatePlatformWindows();
			ForgeUI::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}


	}

	void UI_Layer::OnGUIRender()
	{
		static bool show = true;
		ForgeUI::ShowDemoWindow(&show);
		
	}
	





}
