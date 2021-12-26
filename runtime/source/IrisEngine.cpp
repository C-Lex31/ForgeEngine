//#include <iostream>
#include <IrisEngine.h>
#include "imgui.h"

class Test_Layer :public Iris::Layer
{
public:
	Test_Layer()
		:Layer("Base")
	{};

	void OnUpdate() override
	{
	//	IR_INFO("BaseLayer::Update");
		if (Iris::input::isKeyPressed(IR_KEY_TAB))
			IR_TRACE("TAB press detected");
		if (Iris::input::isKeyPressed(IR_KEY_CAPS_LOCK))
			IR_TRACE("CAPS press detected");
	}

	virtual void OnGUIRender () override
	{
		ImGui::Begin("Render Test");
		ImGui::Text("Prakhar");
		ImGui::End();
	}

	void OnEvent(Iris::Event& event)override
	{
		//IR_INFO("{0}", event);
	}

};

class Sandbox :public Iris::Application
{
public:
	Sandbox()
	{
		PushLayer(new Test_Layer());   
	//	PushOverlay(new Test_Layer());
	}
	~Sandbox()
	{

	}
	
};

Iris::Application* Iris::CreateApplication()
{
	return new Sandbox();
}
