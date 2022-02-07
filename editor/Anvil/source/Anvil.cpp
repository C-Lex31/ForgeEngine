 //#include <iostream>
#include <ForgeEngine.h>
#include "platform/windows/winInput.h"
#include "ForgeEditor.h"
//#include "Forge3D.h"
#include "GLFW/glfw3.h"
#include "core/client/entry_point.h"
namespace Forge {

	class Anvil :public Application
	{
	public:
		Anvil()
		{
			//PushLayer(new Engine_Layer());
			PushLayer(new ForgeEditor());
		}
		~Anvil()
		{

		}

	};

	Application* CreateApplication()
	{
		return new Anvil();
	}
}