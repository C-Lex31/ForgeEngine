//#include <iostream>
#include <IrisEngine.h>

class Test_Layer :public Iris::Layer
{
public:
	Test_Layer()
		:Layer("Base")
	{};

	void OnUpdate() override
	{
		IR_INFO("BaseLayer::Update");
		if (Iris::input::isKeyPressed(IR_KEY_TAB))
			IR_TRACE("TAB press detected");
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
		//PushOverlay(new Iris::UI_Layer());
	}
	~Sandbox()
	{

	}
};

Iris::Application* Iris::CreateApplication()
{
	return new Sandbox();
}