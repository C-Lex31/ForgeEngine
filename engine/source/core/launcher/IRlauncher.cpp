#include "irpch.h"
#include "IRlauncher.h"
#include "core/events/ApplicationEvent.h"
#include "glad/glad.h" 
#include "core/input/input.h"


namespace Iris {
#define IR_BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)
	Application* Application::s_Instance = nullptr;
	//UI_Layer* m_guiLayer = new UI_Layer();
	Application::Application()
	{
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());//explicit contructor?
		m_Window->SetEventCallback(IR_BIND_EVENT_FN(OnEvent));
		 m_guiLayer = new UI_Layer();
		//m_guiLayer = new UI_Layer();
		PushOverlay(m_guiLayer);

		m_vertexArray.reset(vertex_array::create());

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,   1.0f ,0.3f , 0.02f,1,
			0.5f, -0.5f, 0.0f,    0.5f ,0.4f , 0.17f,1,
			0.0f,  0.5f, 0.0f,    0.0f ,0.8f , 0.02f,1
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
		out vec3 vPos;

		
		void main()
		{
        
		vPos=aPos;
	
		gl_Position = vec4(aPos, 1.0);
		}

	)";

		std::string fragmentSrc = R"(
		
		#version 330 core
		layout(location=0) out vec4 FragColor;
		in vec3 vPos;
		void main()
		{
		 FragColor = vec4(vPos*0.5+0.5, 1.0f);
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
		//WindowResizeEvent e(270, 180);//Creating parameterized obj of class WindowResizeEvent
		//IR_TRACE(e);
		while (m_running)
		{

			glClearColor(0.2, 0.2, 0.2, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_shader->bind();
			m_vertexArray->bind();
				glDrawElements(GL_TRIANGLES,m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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