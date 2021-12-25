#pragma once

#include <memory>
#include "buffers.h"

namespace Iris {

	class vertex_array
	{
	public:
		virtual ~vertex_array() = default;
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<vertex_buffer>& vb)  = 0;

		virtual void SetIndexBuffer(const std::shared_ptr<index_buffer>& ib) = 0;

		//TODO: Add Index buffer to array

		static vertex_array* create();
	};



}