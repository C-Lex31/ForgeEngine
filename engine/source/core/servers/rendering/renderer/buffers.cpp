#include "irpch.h"
#include "buffers.h"
#include "renderer_rd.h"
#include "core/drivers/OpenGL/opengl_buffer.h"
namespace Iris {

	vertex_buffer* vertex_buffer::create(float* vertices, uint32_t size)
	{
		switch (renderer::get_api())
		{
		case renderer_api::api:: None  : return nullptr;
		case renderer_api::api:: OpenGL: return new OpenGLVertexBuffer(vertices,size) ;
		}
		return 0;
	}
	index_buffer* index_buffer::create(uint32_t* indices, uint32_t size)
	{
		switch (renderer::get_api())
		{
		case renderer_api::api::None  :     return nullptr;
		case renderer_api::api::OpenGL:     return new OpenGLIndexBuffer(indices, size);
		}

		return nullptr;
		return 0;
	}


}