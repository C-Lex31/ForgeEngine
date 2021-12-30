#include "irpch.h"
#include "render_commands.h"
#include "core/drivers/OpenGL/opengl_renderer.h"
namespace Iris {

	renderer_api* render_commands::s_renderer_api = new OpenGLRendererAPI();

}