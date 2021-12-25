#pragma once

#include "core/layers.h"
//#include "core/IRlauncher.h"
#include "core/events/MouseEvents.h"
#include "core/events/KeyEvents.h"
#include "core/events/ApplicationEvent.h"


namespace Iris {
	class  UI_Layer :public Layer
	{
	public:
		UI_Layer();
		~UI_Layer()=default;

		
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnGUIRender() override;
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;

	};



}
