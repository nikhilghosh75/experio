#include "DemoProjectEditorMainLoop.h"
#include "RuntimeObjectSystem/RuntimeInclude.h"
#include "RuntimeObjectSystem/RuntimeLinkLibrary.h"
#include "RuntimeObjectSystem/IObject.h"
#include "DemoProjectSystemTable.h"
#include "RuntimeObjectSystem/ISimpleSerializer.h"
#include "RuntimeObjectSystem/IRuntimeObjectSystem.h"
#include "RuntimeObjectSystem/IObjectFactorySystem.h"
#include "RuntimeObjectSystem/RuntimeSourceDependency.h"
#include <iostream>

struct RCCppMainLoop : IRCCppMainLoop, TInterface<IID_ENDInterfaceID, IObject>
{
	RCCppMainLoop()
	{
		PerModuleInterface::g_pSystemTable->mainLoop = this;
		g_pSys->runtimeObjectSystem->GetObjectFactorySystem()->SetObjectConstructorHistorySize(0);
		std::cout << "New Main Loop Constructed" << std::endl;
	}

	void Serialize(ISimpleSerializer *pSerializer) override
	{
	}

	void MainLoop() override
	{
		std::cout << "TEST 2" << std::endl;
	}
};

REGISTERSINGLETON(RCCppMainLoop, true);