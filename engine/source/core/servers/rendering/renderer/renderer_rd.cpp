#include "irpch.h"
#include "renderer_rd.h"

namespace Iris {

	 void renderer::IR_BeginScene()
	 {

	 }
	 void renderer::IR_EndScene()
	 {

	 }
	 void renderer::IR_Submit(const std::shared_ptr<vertex_array>& va)
	 {
		 va->bind();
		 render_commands::drawElements(va);
	 }
}