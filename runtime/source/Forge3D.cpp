#include "Forge3D.h"
#include "ForgeEngine.h"

Forge3D::Forge3D()
	:Layer("Forge3D"),m_Cam(1366, 705, glm::vec3(0, 0, 2))
{
}

void Forge3D::OnAttach()
{
	m_Texture2D = Forge::Texture2D::create("assets/textures/brick.png");
	
}

void Forge3D::OnDetach()
{
}

void Forge3D::OnUpdate(Forge::Timestep ts)
{
	
	m_Cam.CamInput(ts.GetSec());
	m_Cam.RecalculateViewMatrix();
	
	Forge::render_commands::SetClearColor({ 0.2, 0.2, 0.2, 1 });
	Forge::render_commands::clear();

	Forge::Renderer3D::BeginScene(m_Cam);

	Forge::Renderer3D::DrawPyramid({-1.0f,0.0f,-1.0f}, {1.0f,1.0f,1.0f},m_Texture2D);
	Forge::Renderer3D::DrawCube({ 1.0f,0.0f,0.0f }, { 0.2f,0.2f,0.2f }, CubeColor);

	Forge::Renderer3D::EndScene();
}

void Forge3D::OnGUIRender()
{
	ForgeUI::Begin("Settings");
	ForgeUI::ColorEdit4("Cube Color", glm::value_ptr(CubeColor));
	ForgeUI::End();
}

void Forge3D::OnEvent(Forge::Event& event)
{
}
