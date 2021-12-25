#pragma once
#include <string>
namespace Iris {


	class shader
	{
	public:
		shader(const std::string& vertexSrc, const std::string& fragSrc);
		~shader();
		void bind() const;
		void unbind() const;

	private:
		uint32_t m_rendererID;
	};

}