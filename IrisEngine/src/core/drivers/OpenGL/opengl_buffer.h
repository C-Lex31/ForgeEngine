#pragma once
#include"core/servers/rendering/renderer/buffers.h"

namespace Iris {
	class OpenGLVertexBuffer:public vertex_buffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		virtual void bind() const ;
		virtual void unbind() const ;

	private:
	uint32_t m_rendererID;
	};

	
	




}