#include "Framework/ImportSystem.h"
#include "Runtime/Debug/Debug.h"

EImportHandlerResult ImportText(FImportInfo info)
{
	Debug::Log("Imported");
	return EImportHandlerResult::NotHandled;
}

IMPORT_FUNCTION(ImportText);