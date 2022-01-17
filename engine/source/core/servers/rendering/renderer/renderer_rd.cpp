#include "frpch.h"
#include "renderer_rd.h"

namespace Forge {
	renderer::SceneData* renderer::m_SceneData = new renderer::SceneData();

	 void renderer::IR_BeginScene(orthographic_camera2d& cam)
	 {
		 m_SceneData->ViewProjectionatrix = cam.GetViewProjectionMatrix();
	 }
	 void renderer::IR_EndScene()
	 {

	 }
	 void renderer::IR_Submit(const std::shared_ptr<vertex_array>& va, const std::shared_ptr<shader>& sh)
	 {
		 sh->bind();
		 va->bind();
		 sh->UploadUniformMat4("u_ViewProjectionMatrix",m_SceneData->ViewProjectionatrix );
		 render_commands::drawElements(va);
	 }
}