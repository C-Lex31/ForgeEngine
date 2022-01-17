#pragma once

#include "renderer_api.h"

namespace Forge {
	class render_commands
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_renderer_api->SetClearColor(color);
		}
		inline static void clear()
		{
			s_renderer_api->clear();
		}

		inline static void drawElements(const std::shared_ptr<vertex_array>& va)
		{
			s_renderer_api->drawElements(va);
		}
	private:
		static renderer_api* s_renderer_api;
	};

}
