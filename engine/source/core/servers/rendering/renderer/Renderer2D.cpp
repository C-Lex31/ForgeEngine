#include "frpch.h"
#include "Renderer2D.h"
#include "core/servers/rendering/core_rd/vertex_array.h"
#include "core/servers/rendering/core_rd/shader.h"
#include "glm/gtc/matrix_transform.hpp"
namespace Forge {

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;

	//	float TilingFactor;

		// Editor-only
	//	int EntityID;
	};
	struct RenderDataCache
	{
		FRef<vertex_array> QuadVA;
		FRef<vertex_buffer> QuadVB;
		FRef<shader> TextureShader;
		FRef<Texture2D> WhiteTexture;

	    const uint32_t MaxQuads = 10000;
	    const uint32_t MaxVertices = MaxQuads * 4; 
	    const uint32_t MaxIndices = MaxQuads * 6; // 6 indices per quad 

	

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		
	};
	static RenderDataCache rdc;

	void Renderer2D::Init()
	{
		rdc.QuadVA = vertex_array::create();

		rdc.QuadVB= vertex_buffer::create(rdc.MaxVertices * sizeof(QuadVertex));
		buffer_layout SQ_layout = {
			{"a_Position" ,ShaderDataType::FRfloat3},
			{"a_Color"    ,ShaderDataType::FRfloat4},
			{"a_TexCoord" ,ShaderDataType::FRfloat2}
			
		};
		rdc.QuadVB->SetLayout(SQ_layout);
		rdc.QuadVA->AddVertexBuffer(rdc.QuadVB);
		rdc.QuadVertexBufferBase = new QuadVertex[rdc.MaxVertices];

		uint32_t* QuadIndices = new uint32_t[rdc.MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < rdc.MaxIndices; i += 6)
		{
			QuadIndices[i + 0] = offset + 0;
			QuadIndices[i + 1] = offset + 1;
			QuadIndices[i + 2] = offset + 2;

			QuadIndices[i + 3] = offset + 2;
			QuadIndices[i + 4] = offset + 3;
			QuadIndices[i + 5] = offset + 0;
			offset += 4;
		}
		FRef<index_buffer>QuadIB = index_buffer::create(QuadIndices, rdc.MaxIndices);
		rdc.QuadVA->SetIndexBuffer(QuadIB);
		delete[] QuadIndices;

		

		rdc.TextureShader = shader::create("assets/shaders/TextureShader.fsf");
		uint32_t WhiteTexData = 0xffffffff;
		rdc.WhiteTexture = Texture2D::create(1, 1,&WhiteTexData);
		rdc.TextureShader->bind();
		rdc.TextureShader->UploadUniformInt("u_Texture", 0);

		
	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene( const orthographic_camera& cam2d)
	{
		rdc.TextureShader->bind();
	rdc.TextureShader->UploadUniformMat4("u_ViewProjectionMatrix", cam2d.GetViewProjectionMatrix());
		//rdc.TextureShader->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
		rdc.QuadIndexCount = 0; 
		rdc.QuadVertexBufferPtr = rdc.QuadVertexBufferBase;

	
	
//	rdc.TextureShader->UploadUniformInt("u_Texture2", 1);
	
	}

	void Renderer2D::EndScene()
	{
		uint32_t dataSize = (uint8_t*)rdc.QuadVertexBufferPtr - (uint8_t*)rdc.QuadVertexBufferBase;
		rdc.QuadVB->SetData(rdc.QuadVertexBufferBase, dataSize);

		Clear();
	}
	void Renderer2D::Clear()
	{
	
		
		  
		render_commands::drawElements(rdc.QuadVA, rdc.QuadIndexCount);
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{


		rdc.QuadVertexBufferPtr->Position = position;
		rdc.QuadVertexBufferPtr->Color = color;
		rdc.QuadVertexBufferPtr->TexCoord = { 0,0 };

		rdc.QuadVertexBufferPtr++;

		rdc.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
		rdc.QuadVertexBufferPtr->Color = color;
		rdc.QuadVertexBufferPtr->TexCoord = { 1,0 };

		rdc.QuadVertexBufferPtr++;

		rdc.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
		rdc.QuadVertexBufferPtr->Color = color;
		rdc.QuadVertexBufferPtr->TexCoord = { 1,1};

		rdc.QuadVertexBufferPtr++;

		rdc.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
		rdc.QuadVertexBufferPtr->Color = color;
		rdc.QuadVertexBufferPtr->TexCoord = { 0,1 };

		rdc.QuadVertexBufferPtr++;

		rdc.QuadIndexCount += 6;
		//rdc.TextureShader->UploadUniformFloat4("u_Color", color);
	/*	rdc.TextureShader->UploadUniformFloat4("u_Color", color);
		rdc.WhiteTexture->bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) /*rotation
			glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		rdc.TextureShader->UploadUniformMat4("u_Transform", transform);
		rdc.QuadVA->bind();
		render_commands::drawElements(rdc.QuadVA);
*/
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const FRef<Texture2D>& texture, const FRef<Texture2D>& texture1)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture,texture1);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const FRef<Texture2D>& texture, const FRef<Texture2D>& texture1)
	{
		

	//	rdc.TextureShader->bind();
		rdc.TextureShader->UploadUniformFloat4("u_Color", {1.0,1.0,1.0,1.0});
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) */*rotation*/
			glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		rdc.TextureShader->UploadUniformMat4("u_Transform", transform);
		//rdc.TextureShader->UploadUniformInt("u_Texture", 0);
		texture->bind();
		//texture1->bind(1);
		
		rdc.QuadVA->bind();
		render_commands::drawElements(rdc.QuadVA);

	}

#if ECS
	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		rdc.TextureShader->UploadUniformFloat4("u_Color", color);

		rdc.WhiteTexture->bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) /*rotation*/
			glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		rdc.TextureShader->UploadUniformMat4("u_Transform", transform);
		rdc.QuadVA->bind();
		render_commands::drawElements(rdc.QuadVA);
	}
#endif
	void Renderer2D::DrawQuad(const glm::mat4& transform, const FRef<Texture2D>& texture, const FRef<Texture2D>& texture2)
	{

	}
}