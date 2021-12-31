#include "irpch.h"
#include "IRlauncher.h"
#include "core/events/ApplicationEvent.h"
#include "core/input/input.h"
#include "core/servers/rendering/renderer/renderer_rd.h"

namespace Iris {
#define IR_BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)
	Application* Application::s_Instance = nullptr;
	Application::Application()
		:m_Cam2d(-1.0f,1.0f,-1.0f,1.0f)
	{
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());//explicit contructor?
		m_Window->SetEventCallback(IR_BIND_EVENT_FN(OnEvent));
		 m_guiLayer = new UI_Layer();
		PushOverlay(m_guiLayer);

		m_vertexArray.reset(vertex_array::create());

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,   0.6f ,0.08f , 0.6f,1,  // R G B A format
			0.5f, -0.5f, 0.0f,    0.7f ,0.1f , 0.07f,1,
			0.0f,  0.5f, 0.0f,    0.8f ,0.5f , 0.02f,1
		};

		m_vertexBuffer.reset(vertex_buffer::create(vertices, sizeof(vertices)));

		buffer_layout layout = {
			{"a_position" ,ShaderDataType::IRfloat3},
			{"a_color" ,ShaderDataType::IRfloat4}
		};

		m_vertexBuffer->SetLayout(layout);
		m_vertexArray->AddVertexBuffer(m_vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		m_indexBuffer.reset(index_buffer::create(indices, sizeof(indices)));
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
		m_shader.reset(new shader(vertexSrc, fragmentSrc));
	}
 


	Application::~Application()
	{

	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		//IR_CORE_INFO("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.m_handled)
				break;
		}
	}
	void Application::Run()
	{
		
		while (m_running)
		{
			render_commands::SetClearColor({ 0.2, 0.2, 0.2, 1 });
			render_commands::clear();

			renderer::IR_BeginScene(m_Cam2d);

		
			renderer::IR_Submit(m_vertexArray,m_shader);

			renderer::IR_EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_guiLayer->Begin();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnGUIRender();
				
			}
			m_guiLayer->End();
			
			m_Window->OnUpdate();
		}
	}
}