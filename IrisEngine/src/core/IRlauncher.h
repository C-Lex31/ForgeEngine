#pragma once

#include "core.h"
#include "Events/event.h"
//#include "Windows.h"
#include "platform/windows/windows.h"
#include "core/layerStack.h"
#include "editor/editor_interface.h"

namespace Iris {
	class IRIS_API Application
	{
	public:
		Application();
		virtual~Application();
		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		Window& GetWindow() { return *m_Window; }
		static Application& Get() { return *s_Instance; }

	private:
		std::unique_ptr<Window> m_Window;
		//std::unique_ptr<UI_Layer> m_guiLayer;
		//UI_Layer* m_guiLayer;
		bool m_running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};
	//Defined in client
	Application* CreateApplication();
}