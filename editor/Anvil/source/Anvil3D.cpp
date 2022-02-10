#include "Anvil3D.h"


namespace Forge {
	Anvil3D::Anvil3D()
		:Layer("Anvil"), m_Cam(1366, 705, glm::vec3(0, 0, 2))
	{
	}

	void Anvil3D::OnAttach()
	{
		//m_Texture2D = Texture2D::create("assets/textures/brick.png");
		m_PlankTexture = Texture2D::create("assets/textures/planks.png", 0);
		//	m_PlankTexture2= Texture2D::create("assets/textures/planks.png", 0, "");
		m_PlankSpecular = Texture2D::create("assets/maps/PlanksSpec.png", 1);

		FramebufferSpecs FSpec;
		FSpec.width = 1366;
		FSpec.height = 705;
		m_Framebuffer = Framebuffer::create(FSpec);
	}

	void Anvil3D::OnDetach()
	{
	}

	void Anvil3D::OnUpdate(Timestep ts)
	{

		m_Cam.CamInput(ts.GetSec());
		m_Cam.RecalculateViewMatrix();

		m_Framebuffer->bind();
		render_commands::SetClearColor({ 0.2, 0.2, 0.2, 1 });
		render_commands::clear();

		Renderer3D::BeginScene(m_Cam);

		//Renderer3D::DrawPyramid({-0.0f,-0.49f,-0.1f}, {0.6f,0.6f,0.6f},m_Texture2D,LightColor,LightPos);
		Renderer3D::DrawPlane({ 0.0f,-0.5f,0.0f }, { 5.0f,0.0f,5.0f }, m_PlankTexture, m_PlankSpecular, LightColor, LightPos);
		//Renderer3D::DrawCube({ 1.0f,0.0f,0.0f }, { 0.2f,0.2f,0.2f }, CubeColor);
		Renderer3D::DrawCube(LightPos, { 0.3f,0.3f,0.3f }, LightColor);
		Renderer3D::EndScene();

		m_Framebuffer->unbind();
	}

	void Anvil3D::OnGUIRender()
	{
      static bool OnDockspace = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace ", &OnDockspace, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }


        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                if (ImGui::MenuItem("Quit")) { Application::Get().Close(); }


                ImGui::EndMenu();
            }


            ImGui::EndMenuBar();
        }
        ImGui::Begin("Settings");
        ImGui::Begin("Settings");
        ImGui::ColorEdit4("Cube Color", glm::value_ptr(CubeColor));
        ImGui::End();
        uint32_t TexID = m_Framebuffer->GetColorAttachmentID();
        ImGui::Image((void*)TexID, ImVec2(1366.0f, 705.0f),ImVec2(0,1) , ImVec2(1,0));
        ImGui::End();

        ImGui::End();

	}

	void Anvil3D::OnEvent(Event& event)
	{
	}
}