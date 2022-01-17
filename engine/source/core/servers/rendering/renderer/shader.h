#pragma once
 #include <string>

#include <glm/glm.hpp>

namespace Forge {


	class shader
	{
	public:
		shader(const std::string& vertexSrc, const std::string& fragSrc);
		~shader();
		void bind() const;
		void unbind() const;

		void UploadUniformMat4(const std::string& name ,const glm::mat4& matrix);

	private:
		uint32_t m_rendererID;
	};

}