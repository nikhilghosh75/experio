#include "CodeGenerator.h"
#include "LSerializationOperations.h"
#include "../CodeParser/Cpp/CppCodeStream.h"
#include "../Framework/EditorProject.h"
#include "../Framework/Values.h"
#include "Runtime/Containers/LString.h"

void CodeGenerator::GenerateAllFiles()
{
	GenerateTagFile();
	GenerateComponentManager();
	GenerateProjectFile();
	GenerateComponentSerializers();
}

void CodeGenerator::GenerateComponentManager()
{
	CodeClass componentManager = GenerateComponentManagerClass();

	// Generate .h file
	CppCodeOStream hFile("DemoProjectComponentManager.h");
	hFile << "#include \"Runtime/Framework/ComponentManager.h\"" << Debug::endl;
	hFile << "#include \"Runtime/DefaultComponents.h\"" << Debug::endl << Debug::endl;
	hFile << componentManager;
	hFile.Close();

	// Generate .cpp file
	CppCodeOStream cppFile("DemoProjectComponentManager.cpp");
	cppFile << "#include \"DemoProjectComponentManager.h\"" << Debug::endl;
	cppFile << "#include \"Runtime/Debug/Debug.h\"" << Debug::endl << Debug::endl;

	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		if (!info.isDefaultComponent)
		{
			cppFile << "#include \"" << info.filepath << "\"" << Debug::endl;
		}
	});

	GenerateComponentManagerStartImpl(cppFile, componentManager);
	GenerateComponentManagerUpdateImpl(cppFile, componentManager);
	GenerateComponentManagerRenderSceneImpl(cppFile, componentManager);
	GenerateComponentManagerDeleteComponentImpl(cppFile, componentManager);
	GenerateComponentManagerGetComponentAtIndexImpl(cppFile, componentManager);
	GenerateComponentManagerOnGameObjectDeletedImpl(cppFile, componentManager);
	GenerateComponentManagerGetComponentIDsImpl(cppFile, componentManager);
	GenerateComponentManagerGetAllComponentsImpl(cppFile, componentManager);
	GenerateComponentManagerCountImpl(cppFile, componentManager);
}

void CodeGenerator::GenerateProjectFile()
{
	GenerateProjectHFile();
	GenerateProjectCppFile();
}

void CodeGenerator::GenerateComponentSerializers()
{
}

void CodeGenerator::GenerateTagFile()
{
	CppCodeOStream outFile("DemoProjectTag.cpp");

	outFile << "#include <cstring>" << Debug::endl;
	outFile << "#include <string>" << Debug::endl << Debug::endl;

	outFile << "#ifndef EXPERIO_EDITOR" << Debug::endl;

	outFile << "unsigned short DefaultTagStringToNum(const char* string)" << Debug::endl;
	outFile << "{" << Debug::endl;

	ExperioEditor::GetTags().ForEach([&outFile](const uint16_t& key, const std::string& value) {
		outFile << "if(strcmp(string, \"" << value << "\")) { return " << std::to_string(key) << "; }" << Debug::endl;
	});

	outFile << "	return 0;" << Debug::endl;
	outFile << "}" << Debug::endl;
	
	outFile << "std::string DefaultTagNumToString(unsigned short num)" << Debug::endl;
	outFile << "{" << Debug::endl;
	outFile << "	switch(num)" << Debug::endl;
	outFile << "	{" << Debug::endl;

	ExperioEditor::GetTags().ForEach([&outFile](const uint16_t& key, const std::string& value) {
		outFile << "case " << key << ": " << "return \"" << value << "\";" << Debug::endl;
	});

	outFile << "	}" << Debug::endl;
	outFile << "	return \"Tag\";" << Debug::endl;
	outFile << "}" << Debug::endl;

	outFile << "#endif" << Debug::endl;
}

CodeClass CodeGenerator::GenerateComponentManagerClass()
{
	CodeClass codeClass("DemoProjectComponentManager");
	codeClass.inheritance.push_back("ComponentManager");

	CodeFunction start("void", "Start");
	start.accessType = ECodeAccessType::Public;
	start.keywords = ECodeFunctionKeyword::Virtual;
	codeClass.functions.push_back(start);
	
	CodeFunction update("void", "Update");
	update.keywords = ECodeFunctionKeyword::Virtual;
	codeClass.functions.push_back(update);

	CodeFunction renderScene("void", "RenderScene");
	renderScene.keywords = ECodeFunctionKeyword::Virtual;
	codeClass.functions.push_back(renderScene);

	CodeFunction addComponent("Component*", "AddComponent");
	addComponent.keywords = ECodeFunctionKeyword::Virtual;
	addComponent.arguments.emplace_back("GameObject*", "gameObject", false);
	addComponent.arguments.emplace_back("unsigned int", "classId", false);
	codeClass.functions.push_back(addComponent);

	CodeFunction getComponent("Component*", "GetComponent");
	getComponent.keywords = ECodeFunctionKeyword::Virtual;
	getComponent.arguments.emplace_back("GameObject*", "gameObject", false);
	getComponent.arguments.emplace_back("unsigned int", "classId", false);
	codeClass.functions.push_back(getComponent);

	CodeFunction getComponentIndex("Component*", "GetComponentAtIndex");
	getComponentIndex.keywords = ECodeFunctionKeyword::Virtual;
	getComponentIndex.arguments.emplace_back("GameObject*", "gameObject", false);
	getComponentIndex.arguments.emplace_back("unsigned int", "classId", false);
	codeClass.functions.push_back(getComponentIndex);

	CodeFunction deleteComponent("void", "DeleteComponent");
	deleteComponent.keywords = ECodeFunctionKeyword::Virtual;
	deleteComponent.arguments.emplace_back("GameObject*", "gameObject", false);
	deleteComponent.arguments.emplace_back("unsigned int", "classId", false);
	codeClass.functions.push_back(deleteComponent);

	CodeFunction onGameObjectDeleted("void", "OnGameObjectDeleted");
	onGameObjectDeleted.keywords = ECodeFunctionKeyword::Virtual;
	onGameObjectDeleted.arguments.emplace_back("GameObject*", "gameObject", false);
	codeClass.functions.push_back(onGameObjectDeleted);

	CodeFunction getComponentIDs("std::vector<unsigned int>", "GetComponentsIDsInGameObject");
	getComponentIDs.keywords = ECodeFunctionKeyword::Virtual;
	getComponentIDs.arguments.emplace_back("GameObject*", "gameObject", false);
	codeClass.functions.push_back(getComponentIDs);

	CodeFunction getComponents("std::vector<Component*>", "GetComponentsInGameObject");
	getComponents.keywords = ECodeFunctionKeyword::Virtual;
	getComponents.arguments.emplace_back("GameObject*", "gameObject", false);
	codeClass.functions.push_back(getComponents);

	CodeFunction getAllComponents("std::vector<Component*>", "GetAllComponents");
	getAllComponents.keywords = ECodeFunctionKeyword::Virtual;
	codeClass.functions.push_back(getAllComponents);

	getAllComponents.arguments.emplace_back("std::vector<Component*>&", "components", false);
	getAllComponents.arguments.emplace_back("std::vector<unsigned int>&", "componentIds", false);
	codeClass.functions.push_back(getAllComponents);

	getAllComponents.arguments.emplace_back("uint8_t", "sceneIndex", false);
	codeClass.functions.push_back(getAllComponents);

	CodeFunction componentCount("unsigned int", "ComponentCount");
	componentCount.keywords = ECodeFunctionKeyword::VirtualConst;
	codeClass.functions.push_back(componentCount);

	EditorProject::componentClasses.ForEach([&codeClass](const unsigned int& id, const FComponentInfo& info) {
		if (!info.isStandaloneComponent) return;

		std::string paramType = "std::vector<" + info.name + ">";
		std::string paramName = LString::ToCamelCase(info.name) + "Instances";
		codeClass.params.emplace_back(paramType, paramName, ECodeAccessType::Public);
	});

	return codeClass;
}

void CodeGenerator::GenerateComponentManagerStartImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "void " << codeClass.name << "::Start()" << Debug::endl << "{" << Debug::endl;

	for (int i = 0; i < codeClass.params.size(); i++)
	{
		cppFile << "PB_START(" << codeClass.params[i].name << ");" << Debug::endl;
	}

	cppFile << "}" << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerUpdateImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "void " << codeClass.name << "::Update()" << Debug::endl << "{" << Debug::endl;
	cppFile << "CameraSystem::Update();" << Debug::endl;

	for (int i = 0; i < codeClass.params.size(); i++)
	{
		cppFile << "PB_UPDATE(" << codeClass.params[i].name << ");" << Debug::endl;
	}

	cppFile << "}" << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerRenderSceneImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "void " << codeClass.name << "::RenderScene()" << Debug::endl << "{" << Debug::endl;
	cppFile << "CameraSystem::Update();" << Debug::endl;
	cppFile << "PB_UPDATE(meshComponentInstances);" << Debug::endl;
	cppFile << "PB_UPDATE(particleSystemInstances);" << Debug::endl;
	cppFile << "PB_UPDATE(billboardInstances);" << Debug::endl;
	cppFile << "}" << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerAddComponentImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "Component* " << codeClass.name << "::AddComponent(GameObject* gameObject, unsigned int classId)"
		<< Debug::endl << "{" << Debug::endl;
	cppFile << "switch(classId)" << Debug::endl << "{" << Debug::endl;
	cppFile << "case 100: return CameraSystem::AddComponent(gameObject);" << Debug::endl;
	
	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		if (info.isStandaloneComponent)
		{
			std::string paramName = LString::ToCamelCase(info.name) + "Instances";
			cppFile << "case " << std::to_string(id) << ": PB_ADD_COMPONENT(" << paramName << ");" << Debug::endl;
		}
	});

	cppFile << "}" << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerGetComponentImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "Component* " << codeClass.name << "::GetComponent(GameObject* gameObject, unsigned int classId)"
		<< Debug::endl << "{" << Debug::endl;
	cppFile << "switch(classId)" << Debug::endl << "{" << Debug::endl;
	cppFile << "case 100: return CameraSystem::GetComponent(gameObject);" << Debug::endl;

	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		if (info.isStandaloneComponent)
		{
			std::string paramName = LString::ToCamelCase(info.name) + "Instances";
			cppFile << "case " << std::to_string(id) << ": PB_GET_COMPONENT(" << paramName << ");" << Debug::endl;
		}
	});

	cppFile << "}" << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerGetComponentAtIndexImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "Component* " << codeClass.name << "::GetComponentAtIndex(unsigned int classId, unsigned int index)"
		<< Debug::endl << "{" << Debug::endl;
	cppFile << "switch(classId)" << Debug::endl << "{" << Debug::endl;
	cppFile << "case 100: Debug::Log(\"CameraSystem has not implemented GetComponentAtIndex\"); return nullptr;" << Debug::endl;

	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		if (info.isStandaloneComponent)
		{
			std::string paramName = LString::ToCamelCase(info.name) + "Instances";
			cppFile << "case " << std::to_string(id) << ": PB_GET_COMPONENT_INDEX(" << paramName << ");" << Debug::endl;
		}
	});

	cppFile << "}" << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerDeleteComponentImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "Component* " << codeClass.name << "::DeleteComponent(GameObject* gameObject, unsigned int classId)"
		<< Debug::endl << "{" << Debug::endl;
	cppFile << "bool foundComponent = false;" << Debug::endl << Debug::endl;
	cppFile << "switch(classId)" << Debug::endl << "{" << Debug::endl;
	cppFile << "case 100: return CameraSystem::DeleteComponent(gameObject);" << Debug::endl;

	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		if (info.isStandaloneComponent)
		{
			std::string paramName = LString::ToCamelCase(info.name) + "Instances";
			cppFile << "case " << std::to_string(id) << ": PB_DELETE_COMPONENT(" << paramName << ");" << Debug::endl;
		}
	});

	cppFile << "}" << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerOnGameObjectDeletedImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "Component* " << codeClass.name << "::OnGameObjectDeleted(GameObject* gameObject, unsigned int classId)"
		<< Debug::endl << "{" << Debug::endl;
	cppFile << "bool foundComponent = false;" << Debug::endl << Debug::endl;
	cppFile << "CameraSystem::OnGameObjectDeleted(gameObject);" << Debug::endl;

	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		if (info.isStandaloneComponent)
		{
			std::string paramName = LString::ToCamelCase(info.name) + "Instances";
			cppFile << "PB_DELETE_COMPONENT(" << paramName << "); foundComponent = false;" << Debug::endl;
		}
	});

	cppFile << "}" << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerGetComponentIDsImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "std::vector<unsigned int> " << codeClass.name << "::GetComponentsIDsInGameObject(GameObject* gameObject)"
		<< Debug::endl << "{" << Debug::endl;
	cppFile << "std::vector<unsigned int> returnVector;" << Debug::endl << Debug::endl;

	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		cppFile << "PB_GET_COMPONENT_IDS(" << std::to_string(id) << ");" << Debug::endl;
	});

	cppFile << "return returnVector;" << Debug::endl;
	cppFile << "}" << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerGetComponentPointersImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "std::vector<Component*> " << codeClass.name << "::GetComponentsInGameObject(GameObject * gameObject)"
		<< Debug::endl << "{" << Debug::endl;
	cppFile << "std::vector<unsigned int> returnVector;" << Debug::endl << Debug::endl;
	cppFile << "returnVector.reserve(ComponentCount());" << Debug::endl;

	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		cppFile << "PB_GET_COMPONENT_GAMEOBJECT(" << std::to_string(id) << ");" << Debug::endl;
	});

	cppFile << "return returnVector;" << Debug::endl;
	cppFile << "}" << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerGetAllComponentsImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	// 0 args
	cppFile << "std::vector<Component*> " << codeClass.name << "::GetAllComponents()" << Debug::endl << "{" << Debug::endl;
	cppFile << "std::vector<Component*> returnVector;" << Debug::endl;
	cppFile << "returnVector.reserve(ComponentCount());" << Debug::endl;

	for (int i = 0; i < codeClass.params.size(); i++)
	{
		cppFile << "PB_GET_ALL(" << codeClass.params[i].name << ");" << Debug::endl;
	}

	cppFile << "return returnVector;" << Debug::endl;
	cppFile << "}" << Debug::endl;

	// 2 arg
	cppFile << "void " << codeClass.name 
		<< "::GetAllComponents(std::vector<Component*>& components, std::vector<unsigned int>& componentIds)" 
		<< Debug::endl << "{" << Debug::endl;
	cppFile << "components.reserve(ComponentCount());" << Debug::endl;
	cppFile << "componentIds.reserve(ComponentCount());" << Debug::endl << Debug::endl;

	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		if (info.isStandaloneComponent)
		{
			std::string paramName = LString::ToCamelCase(info.name) + "Instances";
			cppFile << "PB_GET_ALL_IDS(" << paramName << ", " << std::to_string(id) << ");" << Debug::endl;
		}
	});

	cppFile << "}" << Debug::endl;

	// 2 arg
	cppFile << "void " << codeClass.name
		<< "::GetAllComponents(std::vector<Component*>& components, std::vector<unsigned int>& componentIds)"
		<< Debug::endl << "{" << Debug::endl;
	cppFile << "components.reserve(ComponentCount());" << Debug::endl;
	cppFile << "componentIds.reserve(ComponentCount());" << Debug::endl << Debug::endl;

	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		if (info.isStandaloneComponent)
		{
			std::string paramName = LString::ToCamelCase(info.name) + "Instances";
			cppFile << "PB_GET_ALL_SCENE_IDS(" << paramName << ", " << std::to_string(id) << ");" << Debug::endl;
		}
	});

	cppFile << "}" << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerCountImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "unsigned int " << codeClass.name << "::ComponentCount() const" << Debug::endl << "{" << Debug::endl;
	cppFile << "return CameraSystem::Size()";
	for (int i = 0; i < codeClass.params.size(); i++)
	{
		cppFile << " + " << codeClass.params[i].name << ".size()";
	}
	cppFile << ";" << Debug::endl << "}";
}

void CodeGenerator::GenerateProjectHFile()
{
	CppCodeOStream hFile("DemoProject.h");

	hFile << "#include \"Runtime/Core/Application.h\"" << Debug::endl;
	hFile << "#include \"Runtime/Framework/Project.h\"" << Debug::endl;
	hFile << "#include \"Runtime/Rendering/Renderer.h\"" << Debug::endl;
	hFile << "#include \"Runtime/Time/GameTime.h\"" << Debug::endl;
	hFile << Debug::endl;
	hFile << "#include \"DemoProjectComponentManager.h\"" << Debug::endl;
	hFile << "#include \"DemoProjectMaterialManager.h\"" << Debug::endl;
	hFile << "#include <Windows.h>" << Debug::endl;
	hFile << Debug::endl;

	CodeFunction setupProject("void", "SetupProject");
	CodeFunction runProject("void", "Runtime");
	CodeFunction update("void", "Update");
	CodeFunction createComponentManager("ComponentManager*", "CreateComponentManager");
	CodeFunction createMaterialManager("MaterialManager*", "CreateMaterialManager");

	hFile << "extern \"C\" __declspec(dllexport) " << setupProject << Debug::endl;
	hFile << "extern \"C\" __declspec(dllexport) " << runProject << Debug::endl;
	hFile << "extern \"C\" __declspec(dllexport) " << update << Debug::endl;
	hFile << "extern \"C\" __declspec(dllexport) " << createComponentManager << Debug::endl;
	hFile << "extern \"C\" __declspec(dllexport) " << createMaterialManager << Debug::endl;
}

void CodeGenerator::GenerateProjectCppFile()
{
	CppCodeOStream cppFile("DemoProject.cpp");

	cppFile << "#include \"DemoProject.h\"" << Debug::endl;
	cppFile << "#include \"Runtime/Core/Window.h\"" << Debug::endl;
	cppFile << "#include \"Runtime/Framework/BinaryParams.h\"" << Debug::endl;
	cppFile << "#include \"Runtime/Framework/Params.h\"" << Debug::endl;
	cppFile << "#include \"ThirdParty/Nameof/nameof.hpp\"" << Debug::endl << Debug::endl;

	cppFile << "std::string projectName = \"" << EditorProject::projectName << "\";" << Debug::endl << Debug::endl;

	cppFile << "template <class T> unsigned int DefaultClassTypeToInt() { return 0; }" << Debug::endl << Debug::endl;

	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		cppFile << "template<> unsigned int DefaultClassTypeToInt<" << info.name << ">() "
			<< "{ return " << std::to_string(id) << "; }" << Debug::endl;
	});
	cppFile << Debug::endl;

	cppFile << "template <class T> std::string DefaultClassTypeToString() { return NAMEOF_TYPE(T); }" << Debug::endl;
	cppFile << Debug::endl;

	GenerateSetupProjectImpl(cppFile);
	GenerateRunProjectImpl(cppFile);
	GenerateCreateComponentManagerImpl(cppFile);
	GenerateCreateMaterialManagerImpl(cppFile);
}

void CodeGenerator::GenerateSetupProjectImpl(CppCodeOStream & cppFile)
{
	cppFile << "extern \"C\" __declspec(dllexport) void SetupProject()" << Debug::endl << "{" << Debug::endl;
	cppFile << "Project::componentManager = new DemoProjectComponentManager();" << Debug::endl;
	cppFile << "Project::materialManager = new DemoProjectMaterialManager();" << Debug::endl;
	cppFile << "}" << Debug::endl;
}

void CodeGenerator::GenerateRunProjectImpl(CppCodeOStream & cppFile)
{
	cppFile << "extern \"C\" __declspec(dllexport) void RunProject()" << Debug::endl << "{" << Debug::endl;
	cppFile << "Application app;" << Debug::endl;
	cppFile << "app.Run();" << Debug::endl;
	cppFile << "}" << Debug::endl;
}

void CodeGenerator::GenerateCreateComponentManagerImpl(CppCodeOStream & cppFile)
{
	cppFile << "extern \"C\" __declspec(dllexport) ComponentManager* CreateComponentManager()" << Debug::endl << "{" << Debug::endl;
	cppFile << "return new DemoProjectComponentManager();" << Debug::endl;
	cppFile << "}" << Debug::endl;
}

void CodeGenerator::GenerateCreateMaterialManagerImpl(CppCodeOStream & cppFile)
{
	cppFile << "extern \"C\" __declspec(dllexport) MaterialManager* CreateMaterialManager()" << Debug::endl << "{" << Debug::endl;
	cppFile << "return new DemoProjectMaterialManager();" << Debug::endl;
	cppFile << "}" << Debug::endl;
}
