#include "frpch.h"
#include "opengl_renderer.h"
#include "glad/glad.h"
namespace Forge {

	void OpenGLRendererAPI::Init()
	{

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_DEPTH_TEST);
	}
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
    void OpenGLRendererAPI::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	glDisable(GL_BLEND);
	}
    void OpenGLRendererAPI::drawElements(const FRef<vertex_array>& va)
	{
		glDrawElements(GL_TRIANGLES, va->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);
		//glBindTexture(GL_TEXTURE_2D, 0);
	}
	float OpenGLRendererAPI::GetTime()
	{
		return glfwGetTime();
	}


}