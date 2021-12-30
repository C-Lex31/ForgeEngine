#pragma once

#include "render_commands.h"
namespace Iris {


	class renderer
	{
	public:

		static void IR_BeginScene();
		static void IR_EndScene();

		static void IR_Submit(const std::shared_ptr<vertex_array>& va);

		inline static renderer_api::api get_api() { return renderer_api::getAPI(); }

	};
}
