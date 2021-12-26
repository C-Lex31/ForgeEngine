#include "irpch.h"
#include "opengl_context.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
namespace Iris {

	opengl_context::opengl_context(GLFWwindow* windowHandle)
		:m_windowHandle(windowHandle) {}

	void opengl_context::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		IR_CORE_INFO("Vendor  :{0}", glGetString(GL_VENDOR));
		IR_CORE_INFO("Renderer:{0}", glGetString(GL_RENDERER));
		IR_CORE_INFO("Version :{0}", glGetString(GL_VERSION));
	}
	void opengl_context::swap_buffers()
	{
		
		glfwSwapBuffers(m_windowHandle);
	}
}