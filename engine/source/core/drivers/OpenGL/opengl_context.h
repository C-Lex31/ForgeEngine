#pragma once
#include"core/servers/rendering/renderer/graphics_context.h"
namespace Iris {

	class opengl_context :public graphics_context
	{
	public:
		opengl_context(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void swap_buffers() override;
	private:
		GLFWwindow* m_windowHandle;
	};
}
