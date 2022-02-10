#pragma once

#include "core/core.h"
#include "core/Events/event_register.h"
#include "timestep.h"

#include "platform/windows/windows.h"
#include "core/layers/layerStack.h"
#include "core/editor/editor_interface.h"
#include "core/servers/rendering/renderer/buffers.h"
#include "core/servers/rendering/renderer/vertexArray.h"
#include "core/servers/rendering/renderer/shader.h"

namespace Forge {
	class Application
	{
	public:
		Application(const FString& AppName="");
		virtual~Application();
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	    Window& GetWindow() { return *m_Window; }
		void Close();
		static Application& Get() { return *s_Instance; }
		void test_disp() { printf("Test Pass"); }

	private:
	    FScope<Window> m_Window;
		UI_Layer* m_guiLayer;
		float m_LastFrameTime = 0.0f;
		bool m_running = true;
		LayerStack m_LayerStack;
		

	private:
		static Application* s_Instance;
	};
	//Defined in client
	Application* CreateApplication();
	
}