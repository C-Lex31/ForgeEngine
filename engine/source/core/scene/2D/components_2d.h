#pragma once
#include "glm/glm.hpp"

namespace Forge {

	struct Transform
	{
		glm::mat4 _transform; 
		Transform() = default;

		operator const glm::mat4() const { return _transform; }

	};

	struct SpriteRendererComponent
	{
		glm::vec4 _color;
		SpriteRendererComponent() = default;

		operator const glm::vec4() const { return _color; }
	};

}
