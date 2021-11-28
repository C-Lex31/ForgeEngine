#pragma once

#include "core/layers.h"
#include "core/IRlauncher.h"
#include "core/events/MouseEvents.h"
#include "core/events/KeyEvents.h"
#include "core/events/ApplicationEvent.h"


namespace Iris {
	class IRIS_API UI_Layer :public Layer
	{
	public:
		UI_Layer();
		~UI_Layer();

		virtual void OnUpdate() override;
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		void OnEvent(Event& event);

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;

	};



}
