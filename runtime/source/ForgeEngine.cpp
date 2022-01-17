//#include <iostream>
#include <ForgeEngine.h>
#include "imgui.h"

class Engine_Layer :public Forge::Layer
{
public:
	Engine_Layer()
		:Layer("Base"),m_Cam2d(-1.0f, 1.0f, -1.0f, 1.0f),m_cam2dPos(0.0f),m_cam2dRot(0.0f)
	{
		m_vertexArray.reset(Forge::vertex_array::create());

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,   1.0f ,0.08f ,1.0f,1,  // R G B A format
			0.5f, -0.5f, 0.0f,    0.78f ,0.1f , 0.87f,1,
			0.0f,  0.5f, 0.0f,    0.8f ,0.5f , 0.02f,1
		};

		m_vertexBuffer.reset(Forge::vertex_buffer::create(vertices, sizeof(vertices)));

		Forge::buffer_layout layout = {
			{"a_position" ,Forge::ShaderDataType::IRfloat3},
			{"a_color" ,Forge::ShaderDataType::IRfloat4}
		};

		m_vertexBuffer->SetLayout(layout);
		m_vertexArray->AddVertexBuffer(m_vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		m_indexBuffer.reset(Forge::index_buffer::create(indices, sizeof(indices)));
		m_vertexArray->SetIndexBuffer(m_indexBuffer);

		std::string vertexSrc = R"(

		#version 330 core
		layout (location = 0) in vec3 aPos;
		layout (location =1) in vec4 aColor;
		out vec3 vPos;
		out vec4 vColor;
		uniform mat4 u_ViewProjectionMatrix;		

		void main()
		{
        
		vPos=aPos;
		vColor=aColor;
		gl_Position = u_ViewProjectionMatrix * vec4(aPos, 1.0);
		}

	)";

		std::string fragmentSrc = R"(
		
		#version 330 core
		layout(location=0) out vec4 FragColor;
		in vec3 vPos;
		in vec4 vColor;
		void main()
		{
		 FragColor = vec4(vPos*0.5+0.5, 1.0f);
		 FragColor =vColor;
		}

)";
		m_shader.reset(new Forge::shader(vertexSrc, fragmentSrc));
	
	};

	void OnUpdate() override
	{
		if (Forge::input::isKeyPressed( IR_KEY_A))
			m_cam2dPos.x -= m_cam2dMoveSpeed;
		else if (Forge::input::isKeyPressed(IR_KEY_D))
			m_cam2dPos.x += m_cam2dMoveSpeed;
	    if (Forge::input::isKeyPressed(IR_KEY_W))
			m_cam2dPos.y += m_cam2dMoveSpeed;
		else if (Forge::input::isKeyPressed(IR_KEY_S))
			m_cam2dPos.y -= m_cam2dMoveSpeed;

		if (Forge::input::isKeyPressed(IR_KEY_Q))
			m_cam2dRot += m_cam2dRotSpeed;

		else if (Forge::input::isKeyPressed(IR_KEY_E))
			m_cam2dRot -= m_cam2dRotSpeed;

		    m_Cam2d.SetCamPos(m_cam2dPos);
			m_Cam2d.SetCamRot(m_cam2dRot);
			Forge::render_commands::SetClearColor({ 0.2, 0.2, 0.2, 1 });
			Forge::render_commands::clear();

			Forge::renderer::IR_BeginScene(m_Cam2d);

			Forge::renderer::IR_Submit(m_vertexArray, m_shader);

			Forge::renderer::IR_EndScene();
	}

	virtual void OnGUIRender () override
	{
		ImGui::Begin("Render Test");
		ImGui::Text("Prakhar");
		ImGui::End();
	}

	void OnEvent(Forge::Event& event)override
	{
	
	}

	

private:
	Forge::orthographic_camera2d m_Cam2d;
	std::shared_ptr<Forge::shader> m_shader;
	std::shared_ptr<Forge::vertex_array> m_vertexArray;
	std::shared_ptr<Forge::vertex_buffer> m_vertexBuffer;
	std::shared_ptr<Forge::index_buffer> m_indexBuffer;

	glm::vec3 m_cam2dPos;
	float m_cam2dRot;
	float m_cam2dMoveSpeed=0.04f;
	float m_cam2dRotSpeed = 0.7f;
};

class Sandbox :public Forge::Application
{
public:
	Sandbox()
	{
		PushLayer(new Engine_Layer());   
	}
	~Sandbox()
	{

	}
	
};

Forge::Application* Forge::CreateApplication()
{
	return new Sandbox();
}
