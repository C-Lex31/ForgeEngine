#pragma once

#include "core/layers.h"
#include "core/IRlauncher.h"

namespace Iris {
	class IRIS_API UI_Layer :public Layer
	{
	public:
		UI_Layer();
		~UI_Layer();

		void OnUpdate();
		void OnAttach();
		void OnDetach();
		void OnEvent(Event& event);
	private:
		float m_Time = 0.0f;

	};



}
