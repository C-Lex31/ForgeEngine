#include "irpch.h"
#include "IRlauncher.h"
#include "core/events/ApplicationEvent.h"
#include "glad/glad.h" 
#include "core/input/input.h"

namespace Iris {
#define IR_BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)
	Application* Application::s_Instance = nullptr;
	UI_Layer* m_guiLayer = new UI_Layer();
	Application::Application()
	{
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());//explicit contructor?
		m_Window->SetEventCallback(IR_BIND_EVENT_FN(OnEvent));
		//UI_Layer* m_guiLayer = new UI_Layer();
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
		//WindowResizeEvent e(270, 180);//Creating parameterized obj of class WindowResizeEvent
		//IR_TRACE(e);
		while (m_running)
		{
			
			glClearColor(0.2,0.2,0.2,1);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_guiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnGUIRender();
			m_guiLayer->End();
			
			m_Window->OnUpdate();
		}
	}
}