#include "irpch.h"
#include "winInput.h"
#include "core/launcher/IRlauncher.h"
#//include "GLFW/glfw3.h"

namespace Iris {
	input* input::s_Instance = new winInput();
	bool winInput::isKeyPressedImpl(int keycode) 
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS ||state == GLFW_REPEAT;
	}

	bool winInput::isMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, button);
		return state == GLFW_PRESS ;
	}
	std::pair<float, float> winInput::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return{ (float)xpos ,(float)ypos };
	}

	float winInput::GetMouseXImpl()
	{
		auto [x,y] = GetMousePosImpl();
	
		return (float)x;
	}
	float winInput::GetMouseYImpl()
	{
		auto [x,y] = GetMousePosImpl();
		return (float)y;
	}
}

