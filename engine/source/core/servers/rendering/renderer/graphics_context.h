#pragma once

namespace Iris {

	class graphics_context
	
	{
	public:
		virtual void Init() = 0;
		virtual void swap_buffers() = 0;

	};

}