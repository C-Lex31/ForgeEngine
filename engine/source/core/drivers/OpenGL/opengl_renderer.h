#pragma once

#include "core/servers/rendering/renderer/renderer_api.h"

namespace Forge {

	class OpenGLRendererAPI:public renderer_api
	{
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void clear() override;
	    virtual void drawElements(const std::shared_ptr<vertex_array>& va) override;
	};

}
