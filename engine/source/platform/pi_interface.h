#pragma once

#include <sstream>
#include "core/events/event.h"
#include "core/core.h"
#include "GLFW/glfw3.h"
//#include "glad/glad.h"



namespace Iris {

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "Iris Engine",
			uint32_t width = 1366,
			uint32_t height = 705)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	//To be implemented per platform,its just an interface
	class IRIS_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {};

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;// It returns a void pointer as it doesnt always have to be a glfw window . In future if I decide to use any other Graphics library..it could return HWIN ..etc

		static Window* Create(const WindowProps& props = WindowProps());//implemented per platform
	};

	

}