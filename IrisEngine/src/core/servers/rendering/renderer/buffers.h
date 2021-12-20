#pragma once

namespace Iris {

	enum class ShaderDataType
	{
		None=0,IRfloat,IRfloat2,IRfloat3,IRfloat4,IRvec3,IRvec4,IRint,IRint2,IRint3,IRint4,IRbool
	};

	static uint32_t sdtSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::IRfloat :   return 4;
			case ShaderDataType::IRfloat2:   return 4*2;
			case ShaderDataType::IRfloat3:   return 4*3;
			case ShaderDataType::IRfloat4:   return 4*4;
			case ShaderDataType::IRvec3  :   return 4*3*3;
			case ShaderDataType::IRvec4  :   return 4*4*4;
			case ShaderDataType::IRint   :   return 4;
			case ShaderDataType::IRint2  :   return 4*2;
			case ShaderDataType::IRint3  :   return 4*3;
			case ShaderDataType::IRint4  :   return 4*4;

		}

		return 0;
	}

	struct buffer_elements
	{
		std::string m_name;
		ShaderDataType m_type;
		uint32_t m_size;
		uint32_t m_offset;

		buffer_elements(const std::string& name,ShaderDataType type)
			:m_name(name),m_type(type),m_size(sdtSize(type)),m_offset(0) {}
	};


	class buffer_layout
	{
	public:
		buffer_layout(const std::initializer_list<buffer_elements>& element)
			:m_elements(element)
		{
			CalcOffsetStride();
		}
		inline const std::vector<buffer_elements> getElements() { return m_elements; }
	private:
		void CalcOffsetStride()
		{
			uint32_t offset = 0;
			m_stride = 0;
			for (auto& element : m_elements)
			{
				element.m_offset = offset;
				offset += element.m_size;
				m_stride += element.m_size;
			}
		}
	private:
		std::vector<buffer_elements> m_elements;
		uint32_t m_stride;
	};


	class vertex_buffer
	{
	public:
		virtual ~vertex_buffer() {}
		virtual void bind() const=0;
		virtual void unbind() const= 0;

		static vertex_buffer* create(float* vertices , int size);
	};


	class index_buffer
	{
	public:
		virtual ~index_buffer() {}
		virtual void bind() const=0;
		virtual void unbind() const = 0;
		static index_buffer* create(float* indices, int size);
	};

}
