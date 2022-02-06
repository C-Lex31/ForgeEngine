#include "frpch.h"
#include "Renderer3D.h"
#include "vertexArray.h"
#include "shader.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Forge {

	struct RenderDataCache
	{
		FRef<vertex_array> PyroVA;
		FRef<vertex_array> CubeVA;
		FRef<shader> CubeShader;
		FRef<shader> PyroTexShader;
	};
	static RenderDataCache* rdc;
	void Renderer3D::Init()
	{
		rdc = new RenderDataCache();
		rdc->PyroVA = vertex_array::create();

		float vertices[] = {
			//-----VERTICES---      ----TEXCOORD-----
			-0.5f, 0.0f, 0.5f,       0.0f,0.0f,
			-0.5f, 0.0f, -0.5f,      5.0f,0.0f,
			0.5f,  0.0f, -0.5f,      0.0f,0.0f,
			0.5f ,0.0f, 0.5f,    	 5.0f,0.0f,
			0.0f,0.8f,0.0f ,     	 2.5f,5.0f
		};

		FRef<vertex_buffer>m_vertexBuffer;
		m_vertexBuffer.reset(vertex_buffer::create(vertices, sizeof(vertices)));
		buffer_layout layout = {
			{"aPos" ,ShaderDataType::FRfloat3},
			{"a_TexCoord",ShaderDataType::FRfloat2}
		};

		m_vertexBuffer->SetLayout(layout);
		rdc->PyroVA->AddVertexBuffer(m_vertexBuffer);

		uint32_t indices[] = {
			0,1,2,
			0,2,3,
			0,1,4,
			1,2,4,
			2,3,4,
			3,0,4
		};
		FRef<index_buffer>m_indexBuffer;
		m_indexBuffer.reset(index_buffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
		rdc->PyroVA->SetIndexBuffer(m_indexBuffer);

		rdc->CubeVA = vertex_array::create();
		float CubeVert[] = {
			// front
			 -0.5, -0.5f,  0.5f,	//1.0,0.0,0.0,1.0,        
			 0.5f, -0.5f,  0.5f,	//1.0,0.0,0.0,1.0,
			 0.5f,  0.5f,  0.5f,	//1.0,0.0,0.0,1.0,
			-0.5f,  0.5f,  0.5f,	//1.0,0.0,0.0,1.0,
			// back
			-0.5f, -0.5f, -0.5f,	//1.0,0.0,0.0,1.0,
			 0.5f, -0.5f, -0.5f,	//1.0,0.0,0.0,1.0,
			 0.5f,  0.5f, -0.5f,	//1.0,0.0,0.0,1.0,
			-0.5f,  0.5f, -0.5f,	//1.0,0.0,0.0,1.0
	


		};
		FRef<vertex_buffer>CubeVB;
		CubeVB.reset(vertex_buffer::create(CubeVert, sizeof(CubeVert)));
		buffer_layout CubeLayout = {
			{"a_Pos" ,ShaderDataType::FRfloat3},
		//	{"a_Color",ShaderDataType::FRfloat4}
		};
		CubeVB->SetLayout(CubeLayout);
		rdc->CubeVA->AddVertexBuffer(CubeVB);

		uint32_t CubeIndices[] = {
			// front
			0, 1, 2,
			2, 3, 0,
			// right
			1, 5, 6,
			6, 2, 1,
			// back
			7, 6, 5,
			5, 4, 7,
			// left
			4, 0, 3,
			3, 7, 4,
			// bottom
			4, 5, 1,
			1, 0, 4,
			// top
			3, 2, 6,
			6, 7, 3

		};
		FRef<index_buffer> CubeIB;
		CubeIB.reset(index_buffer::create(CubeIndices, sizeof(CubeIndices) / sizeof(uint32_t)));
		rdc->CubeVA->SetIndexBuffer(CubeIB);

		rdc->CubeShader = shader::create("assets/shaders/CubeShader.fsf");
		rdc->PyroTexShader = shader::create("assets/shaders/PyramidTextureShader.fsf");

	}

	void Renderer3D::Shutdown()
	{
		delete rdc;
	}

	void Renderer3D::BeginScene(const Camera& cam)
	{
		glm::mat4 model = glm::mat4(1.0f);
		rdc->PyroTexShader->bind();
		rdc->PyroTexShader->UploadUniformMat4("u_ViewProjectionMatrix", cam.GetViewProjectionMatrix());
		rdc->PyroTexShader->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
		rdc->PyroTexShader->UploadUniformInt("u_Texture", 0);
	
		rdc->CubeShader->bind();
		rdc->CubeShader->UploadUniformMat4("u_ViewProjectionMatrix", cam.GetViewProjectionMatrix());
		rdc->CubeShader->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
	}

	void Renderer3D::EndScene()
	{
	}

	void Renderer3D::DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color, const glm::mat4& model)
	{
		rdc->CubeShader->bind();
		rdc->CubeShader->UploadUniformFloat4("u_Color", color);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) */*rotation*/
			glm::scale(glm::mat4(1.0f), { size.x,size.y,size.z });
		rdc->CubeShader->UploadUniformMat4("u_Transform", transform);
		rdc->CubeShader->UploadUniformMat4("model", model);
		
		rdc->CubeVA->bind();
		render_commands::drawElements(rdc->CubeVA);
	}

	void Renderer3D::DrawPyramid(const glm::vec3& position, const glm::vec3& size, const FRef<Texture2D>& texture, const glm::mat4& model)
	{
		rdc->PyroTexShader->bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) */*rotation*/
			glm::scale(glm::mat4(1.0f), { size.x,size.y,size.z });
		rdc->PyroTexShader->UploadUniformMat4("u_Transform", transform);
		rdc->PyroTexShader->UploadUniformMat4("model", model);
		texture->bind();
		rdc->PyroVA->bind();
		render_commands::drawElements(rdc->PyroVA);
	}

}