#pragma once

#include "render_commands.h"
#include "core/servers/camera/camera.h"
#include "texture.h"
namespace Forge {

	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& cam);
		static void EndScene();

		static void DrawPlane(const glm::vec3& position, const glm::vec3& size, const FRef<Texture2D>& texture, const FRef<Texture2D>& SpecularMap, const glm::vec4& color, const glm::vec3& LightPos, const glm::mat4& model = glm::mat4(1.0f));
		static void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color, const glm::mat4& model = glm::mat4(1.0f));
		static void DrawPyramid(const glm::vec3& position, const glm::vec3& size, const FRef<Texture2D>& texture, const glm::vec4 LightColor, const glm::vec3& LightPos, const glm::mat4& model = glm::mat4(1.0f));

	};

}

