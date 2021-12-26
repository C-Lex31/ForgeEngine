#pragma once

namespace Iris {

	enum class renderer_api
	{
		None = 0, OpenGL = 1
	};

	class renderer
	{
	public:
		inline static renderer_api get_api() { return s_renderer_api; }
	private:
		static renderer_api s_renderer_api;
	};
}
