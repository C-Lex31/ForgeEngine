#pragma once

namespace Forge {

	class Texture
	{
	public:
	    virtual ~Texture() = default;
		 
		virtual uint32_t GetTexWidth() const = 0;
		virtual uint32_t GetTexHeight() const = 0;
		virtual void bind(uint32_t slot=0) const = 0;
	};

	class Texture2D:public Texture
	{
	public:
		static FRef<Texture2D> create(const FString& path ,  const FString& flag="");

	};
}
