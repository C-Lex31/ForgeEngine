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

		//Added functionality to retrieve what the vertex array stores.
		virtual const std::vector<std::shared_ptr<vertex_buffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<index_buffer>& GetIndexBuffers() const = 0;

		static vertex_array* create();
	};



}