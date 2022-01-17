#pragma once

#include "core/core.h"
#include "core/Events/event_register.h"
//#include "Windows.h"
#include "platform/windows/windows.h"
#include "core/layers/layerStack.h"
#include "core/editor/editor_interface.h"
#include "core/servers/rendering/renderer/buffers.h"
#include "core/servers/rendering/renderer/vertexArray.h"
#include "core/servers/rendering/renderer/shader.h"
#include "core/servers/camera/orthographic_camera2d.h"
namespace Forge {
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
		UI_Layer* m_guiLayer;

		bool m_running = true;
		LayerStack m_LayerStack;
		/*std::shared_ptr<shader> m_shader;
		std::shared_ptr<vertex_array> m_vertexArray;
		std::shared_ptr<vertex_buffer> m_vertexBuffer;
		std::shared_ptr<index_buffer> m_indexBuffer;

	    orthographic_camera2d m_Cam2d;*/

	private:
		static Application* s_Instance;
	};
	//Defined in client
	Application* CreateApplication();
	
}