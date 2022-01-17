#pragma once

#include "render_commands.h"
#include "shader.h"
#include "core/servers/camera/orthographic_camera2d.h"
namespace Forge {


	class renderer
	{
	public:

		static void IR_BeginScene(orthographic_camera2d& cam);
		static void IR_EndScene();

		static void IR_Submit(const std::shared_ptr<vertex_array>& va , const std::shared_ptr<shader>& sh);

		inline static renderer_api::api get_api() { return renderer_api::getAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionatrix;
		};

		static SceneData* m_SceneData;
	};
}
