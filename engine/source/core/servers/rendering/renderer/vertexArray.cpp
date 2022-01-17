#include "frpch.h"
#include "vertexArray.h"
#include "renderer_rd.h"
#include "core/drivers/OpenGL/opengl_vertexArray.h"
namespace Forge {


	vertex_array* vertex_array::create()
	{
		switch (renderer::get_api())
		{
		case renderer_api::api::None: return nullptr;
		case renderer_api::api::OpenGL: return new OpenGLVertexArray();
		}
		return 0;
	}



}