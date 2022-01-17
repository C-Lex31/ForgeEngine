#pragma once


#include "core/core.h"

namespace Forge {

	class FORGE_API input
	{
	public:
		static bool isKeyPressed(int keycode) { return s_Instance->isKeyPressedImpl(keycode) ; }
		static bool isMouseButtonPressed(int button) { return s_Instance->isMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
		
		static bool GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static bool GetMouseY() { return s_Instance->GetMouseYImpl(); }
		//static bool isKeyPressed(int keycode) { return s_Instance->isKeyPressedImpl(keycode); }
	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;
		virtual bool isMouseButtonPressedImpl(int keycode) = 0;
		virtual std::pair<float,float> GetMousePosImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static input* s_Instance;
	};
}
