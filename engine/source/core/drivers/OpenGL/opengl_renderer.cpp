#include "frpch.h"
#include "opengl_renderer.h"
#include "glad/glad.h"
namespace Forge {

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
    void OpenGLRendererAPI::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
    void OpenGLRendererAPI::drawElements(const std::shared_ptr<vertex_array>& va)
	{
		glDrawElements(GL_TRIANGLES, va->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}


}