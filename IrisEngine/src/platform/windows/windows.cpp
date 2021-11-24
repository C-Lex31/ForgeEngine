#include "irpch.h"
#include "core/events/ApplicationEvent.h"
#include "core/events/KeyEvents.h"
#include "core/events/MouseEvents.h"

#include "glad/glad.h"


namespace Iris {

	static bool s_GLFWInitialized = false;
	Window* Window::Create(const WindowProps& props)
	{
		return new MsWin(props);
	}

	MsWin::MsWin(const WindowProps& props)
	{
		Init(props);
	}

	MsWin::~MsWin()
	{
		Shutdown();
	}
	void MsWin::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		
		IR_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			//HZ_CORE_ASSERT(success, "Could not initialize GLFW!");
			//glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* win, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(win);
				WindowResizeEvent event(width, height);
				data.EventCallback(event);
				data.Width = width;
				data.Height = height;
			});


		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});
	}

	void MsWin::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void MsWin::OnUpdate()
	{

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void MsWin::SetVSync(bool enabled)
	{
		//HZ_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool MsWin::IsVSync() const
	{
		return m_Data.VSync;
	}

}