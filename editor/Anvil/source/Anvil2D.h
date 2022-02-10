#pragma once
#include "ForgeEngine.h"

namespace Forge {
	class Anvil :public Layer
	{
	public:
		Anvil();
		virtual ~Anvil() = default;
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		void OnUpdate(Timestep ts) override;
		virtual void OnGUIRender() override;
		void OnEvent(Event& event)override;
	private:
		orthographic_camera2d m_Cam2d;
		FRef<vertex_array> SQvertexArray;

		FRef<shader> m_Shader;
		FRef<Texture2D>m_CheckerboardTexture, m_Logo;
		FRef<Framebuffer>m_Framebuffer;
		glm::vec4 QuadColor1 = { 0.2f, 0.3f, 0.8f, 1.0f };
		glm::vec4 QuadColor2 = { 0.7f, 0.2f, 0.3f, 1.0f };
	};
}