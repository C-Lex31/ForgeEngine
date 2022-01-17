#include "frpch.h"
#include "opengl_vertexArray.h"
#include "glad/glad.h"
namespace Forge {

	static GLenum sdtToGLtype(ShaderDataType type)
	{
		switch (type)
		{
		case Forge::ShaderDataType::IRfloat :  return GL_FLOAT;
		case Forge::ShaderDataType::IRfloat2:  return GL_FLOAT;
		case Forge::ShaderDataType::IRfloat3:  return GL_FLOAT;
		case Forge::ShaderDataType::IRfloat4:  return GL_FLOAT;
		case Forge::ShaderDataType::IRvec3 :   return GL_FLOAT;
		case Forge::ShaderDataType::IRvec4 :   return GL_FLOAT;
		case Forge::ShaderDataType::IRint  :   return GL_INT;
		case Forge::ShaderDataType::IRint2 :   return GL_INT;
		case Forge::ShaderDataType::IRint3 :   return GL_INT;
		case Forge::ShaderDataType::IRint4 :   return GL_INT;
		case Forge::ShaderDataType::IRbool:    return GL_BOOL;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_rendererID);

	}
	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(m_rendererID);
	}

	 void OpenGLVertexArray::unbind() const
	{
		 glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<vertex_buffer>& vb) 
	{
		glBindVertexArray(m_rendererID);
		vb->bind();
		uint32_t index = 0;
		const auto& layout = vb->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), sdtToGLtype(element.m_type), element.isNormalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.m_offset);

			index++;
		}
		m_vertexBuffers.push_back(vb);
	}
	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<index_buffer>& ib)
	{

		glBindVertexArray(m_rendererID);
		ib->bind();
		m_indexBuffers = ib;
	}


}