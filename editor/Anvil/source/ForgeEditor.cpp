#include "ForgeEditor.h"

namespace Forge {
	ForgeEditor::ForgeEditor()
		:Layer("Forge2D"), m_Cam2d(-1.6f, 1.6f, -0.9f, 0.9f)
	{

	}

	void ForgeEditor::OnAttach()
	{



	}

	void ForgeEditor::OnDetach()
	{
	}

	void ForgeEditor::OnUpdate(Timestep ts)
	{
		//--------------------------------------------------2D Camera------------------------------------------------------------------------------------------------------
		m_Cam2d.OrthographicCameraInput(ts.GetSec());
		//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
		Forge::render_commands::SetClearColor({ 0.2, 0.2, 0.2, 1 });
		Forge::render_commands::clear();


		Renderer2D::BeginScene(m_Cam2d);
		Renderer2D::DrawQuad({ 0.0f,0.0f }, { 1.0f,1.0f }, QuadColor1);
		Renderer2D::DrawQuad({ 1.0f,0.0f }, { 0.8f,0.5f }, QuadColor2);
		Renderer2D::EndScene();

	}

	void ForgeEditor::OnGUIRender()
	{
		ForgeUI::Begin("Settings");
		ForgeUI::ColorEdit4("Quad Color 1", glm::value_ptr(QuadColor1));
		ForgeUI::ColorEdit4("Quad Color 2", glm::value_ptr(QuadColor2));
		ForgeUI::End();
	}

	void ForgeEditor::OnEvent(Forge::Event& event)
	{
	}

}
