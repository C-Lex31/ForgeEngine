#include "frpch.h"
#include "main.h"
#include "core/events/ApplicationEvent.h"
#include "core/input/input.h"
#include "core/servers/rendering/renderer/renderer_rd.h"

namespace Forge {
#define FR_BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)
	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());//explicit contructor?
		m_Window->SetEventCallback(FR_BIND_EVENT_FN(OnEvent));
		m_Window->SetVSync(true);
		m_Window->EnableDepthTest();
		renderer::Init();
		 m_guiLayer = new UI_Layer();
		PushOverlay(m_guiLayer);	
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
			float time =(float)render_commands::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

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