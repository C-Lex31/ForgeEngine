#pragma once

#include "core.h"
#include "Events/event.h"
//#include "Windows.h"
#include "platform/windows/windows.h"
#include "core/layerStack.h"
#include "editor/editor_interface.h"
#include "servers/rendering/renderer/buffers.h"
#include "servers/rendering/renderer/vertexArray.h"
#include "servers/rendering/renderer/shader.h"
namespace Iris {
	class Application
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
		void test_disp() { printf("Test Pass"); }
	private:
		std::unique_ptr<Window> m_Window;
		//unique pointer to hold instance of window class.
		//std::unique_ptr<UI_Layer> m_guiLayer;
		//
		UI_Layer* m_guiLayer;

		//Iris::UI_Layer* m_guiLayer = new Iris::UI_Layer();
		bool m_running = true;
		LayerStack m_LayerStack;
		std::shared_ptr<shader> m_shader;
		std::shared_ptr<vertex_array> m_vertexArray;
		std::shared_ptr<vertex_buffer> m_vertexBuffer;
		std::shared_ptr<index_buffer> m_indexBuffer;

	private:
		static Application* s_Instance;
	};
	//Defined in client
	Application* CreateApplication();
	
}