#pragma once

#include "../Runtime/Core/Base.h"

#include "../../Dependencies/RuntimeCompiledCPP/RuntimeCompiler/AUArray.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeCompiler/BuildTool.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeCompiler/CompileOptions.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeCompiler/Compiler.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeCompiler/FileChangeNotifier.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeCompiler/FileSystemUtils.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeCompiler/ICompilerLogger.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeCompiler/IFileChangeNotifier.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeCompiler/SimpleFileWatcher/FileWatcher.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeCompiler/SimpleFileWatcher/FileWatcherImpl.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeCompiler/SimpleFileWatcher/FileWatcherWin32.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeObjectSystem/IObject.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeObjectSystem/IObjectFactorySystem.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeObjectSystem/IRuntimeObjectSystem.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeObjectSystem/ISimpleSerializer.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeObjectSystem/ObjectFactorySystem/ObjectFactorySystem.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeObjectSystem/ObjectInterface.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeObjectSystem/ObjectInterfacePerModule.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeObjectSystem/RuntimeInclude.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeObjectSystem/RuntimeLinkLibrary.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeObjectSystem/RuntimeObjectSystem.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeObjectSystem/RuntimeProtector.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeObjectSystem/RuntimeSourceDependency.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeObjectSystem/RuntimeTracking.h"
#include "../../Dependencies/RuntimeCompiledCPP/RuntimeObjectSystem/SimpleSerializer/SimpleSerializer.h"

#ifdef EXPERIO_EDITOR
#define RCCPP_INTERFACE(x) TInterface< x , IObject>
#else
#define RCCPP_INTERFACE(x) Empty
#endif