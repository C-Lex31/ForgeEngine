#pragma once

#ifdef IR_PLATFORM_WINDOWS

extern Iris::Application* Iris::CreateApplication();

int main(int argc, char** argv)
{
	Iris::Log::Init();
	IR_CORE_WARN("Initialized Log");
	IR_TRACE("READY");

	auto app = Iris::CreateApplication();
	app->Run();
	delete app;
}


#endif 
