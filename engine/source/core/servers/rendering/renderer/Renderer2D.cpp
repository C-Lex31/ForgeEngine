#include "frpch.h"
#include "Renderer2D.h"
#include "vertexArray.h"
#include "shader.h"
#include "glm/gtc/matrix_transform.hpp"
namespace Forge {
	struct RenderDataCache
	{
		FRef<vertex_array> QuadVA;
		FRef<shader> QuadShader;
	};
	static RenderDataCache* rdc;
	void Renderer2D::Init()
	{
		rdc = new RenderDataCache();
		rdc->QuadVA = vertex_array::create();

		float SQvertices[] = {
			-0.5f, -0.5f,0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f,  0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};

		FRef<vertex_buffer>squareVB;
		squareVB.reset(vertex_buffer::create(SQvertices, sizeof(SQvertices)));
		buffer_layout SQ_layout = {
			{"a_position" ,ShaderDataType::FRfloat3},

		};

		squareVB->SetLayout(SQ_layout);
		rdc->QuadVA->AddVertexBuffer(squareVB);

		uint32_t SQindices[6] = { 0,1,2,2,3,0 };

		FRef<index_buffer>squareIB;

		squareIB.reset(index_buffer::create(SQindices, sizeof(SQindices) / sizeof(uint32_t)));
		rdc->QuadVA->SetIndexBuffer(squareIB);

		rdc->QuadShader = shader::create("assets/shaders/QuadShader.fsf");
		//m_TextureShader.reset(shader::create("assets/shaders/PyramidTextureShader.fvs", "assets/shaders/PyramidTextureShader.fps"));
	//	m_Texture2D = Texture2D::create("assets/textures/brick.png");
		//m_TextureShader->bind();
		//m_TextureShader->UploadUniformInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete rdc;
	}

	void Renderer2D::BeginScene( const orthographic_camera2d& cam2d)
	{
		rdc->QuadShader->bind();
		rdc->QuadShader->UploadUniformMat4("u_ViewProjectionMatrix", cam2d.GetViewProjectionMatrix());
		rdc->QuadShader->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		rdc->QuadShader->bind();
		rdc->QuadShader->UploadUniformFloat4("u_Color",color);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) */*rotation*/
			glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		rdc->QuadShader->UploadUniformMat4("u_Transform", transform);
		rdc->QuadVA->bind();
		render_commands::drawElements(rdc->QuadVA);
	}
}