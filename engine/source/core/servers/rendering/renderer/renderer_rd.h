#pragma once

#include "render_commands.h"
#include "shader.h"
#include "core/servers/camera/orthographic_camera2d.h"
#include "core/servers/camera/Camera.h"
namespace Forge {


	class renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void IR_BeginScene(orthographic_camera2d& cam);
		static void IR_BeginScene(Camera& cam);
		static void IR_EndScene();

		static void IR_Submit(const FRef<vertex_array>& va , const FRef<shader>& sh, const glm::mat4& transform =glm::mat4(1.0f), const glm::mat4& model = glm::mat4(1.0f));

		inline static renderer_api::api get_api() { return renderer_api::getAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionatrix;
		};

		static SceneData* m_SceneData;
	};
}
