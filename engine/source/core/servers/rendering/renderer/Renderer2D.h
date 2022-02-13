#pragma once
#include "core/servers/camera/2D/orthographic_camera.h"
#include "render_commands.h"
#include "texture.h"
namespace Forge {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const orthographic_camera& cam2d);
		static void EndScene();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const FRef<Texture2D>& texture, const FRef<Texture2D>& texture2);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const FRef<Texture2D>& texture, const FRef<Texture2D>& texture2);
	};

}
