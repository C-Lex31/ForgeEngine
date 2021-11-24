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
		//IR_INFO("BaseLayer::Update");
	}

	void OnEvent(Iris::Event& event)override
	{
		//IR_TRACE("{0}", event);
	}

};

class Sandbox :public Iris::Application
{
public:
	Sandbox()
	{
		PushLayer(new Test_Layer());   
	//	PushOverlay(new Iris::UI_Layer());
	}
	~Sandbox()
	{

	}
};

Iris::Application* Iris::CreateApplication()
{
	return new Sandbox();
}