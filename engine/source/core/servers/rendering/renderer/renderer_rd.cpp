#include "frpch.h"
#include "renderer_rd.h"
#include "Renderer2D.h"
#include "Renderer3D.h"
namespace Forge {
	renderer::SceneData* renderer::m_SceneData = new renderer::SceneData();

	void renderer::Init()
	{

		render_commands::Init();
		Renderer3D::Init();
		Renderer2D::Init();   
	}

	void renderer::Shutdown()
	{
		Renderer3D::Shutdown();
		Renderer2D::Shutdown();
	}

	 void renderer::IR_BeginScene(orthographic_camera2d& cam)
	 {
		 m_SceneData->ViewProjectionatrix = cam.GetViewProjectionMatrix();
	 }
	 void renderer::IR_BeginScene(Camera& cam)
	 {
		 m_SceneData->ViewProjectionatrix = cam.GetViewProjectionMatrix();
	 }
	 void renderer::IR_EndScene()
	 {

	 }
	 void renderer::IR_Submit(const FRef<vertex_array>& va, const FRef<shader>& sh, const glm::mat4& transform ,const glm::mat4& model)
	 {
		 sh->bind();
		 va->bind();
		 sh->UploadUniformMat4("u_ViewProjectionMatrix",m_SceneData->ViewProjectionatrix );
		 sh->UploadUniformMat4("u_Transform", transform);
		 sh->UploadUniformMat4("model", model);
		 render_commands::drawElements(va);
	 }
}