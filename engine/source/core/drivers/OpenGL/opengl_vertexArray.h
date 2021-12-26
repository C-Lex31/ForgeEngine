#pragma once

#include "core/servers/rendering/renderer/vertexArray.h"

namespace Iris {

	class OpenGLVertexArray:public vertex_array
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() {}
		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<vertex_buffer>& vb) override;
		virtual void SetIndexBuffer(const std::shared_ptr<index_buffer>& ib) override;
		//TODO: Add Index buffer to array

	private:
		std::vector<std::shared_ptr<vertex_buffer>> m_vertexBuffers;
		std::shared_ptr<index_buffer> m_indexBuffers;
		uint32_t m_rendererID;
	};
}