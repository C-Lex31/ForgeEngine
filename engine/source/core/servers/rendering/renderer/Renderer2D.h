#pragma once
#include "core/servers/camera/orthographic_camera2d.h"
#include "render_commands.h"
namespace Forge {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const orthographic_camera2d& cam2d);
		static void EndScene();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	};

}
