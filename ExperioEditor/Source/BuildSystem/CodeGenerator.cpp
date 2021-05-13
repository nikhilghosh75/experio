#include "CodeGenerator.h"
#include "LSerializationOperations.h"
#include "../CodeParser/Cpp/CppCodeStream.h"
#include "../Core/EditorApplication.h"
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
	CppCodeOStream hFile(EditorApplication::sourceFilePath + "/DemoProjectComponentManager.h");
	hFile << "#include \"Runtime/Framework/ComponentManager.h\"" << Debug::endl;
	hFile << "#include \"Runtime/DefaultComponents.h\"" << Debug::endl << Debug::endl;

	EditorProject::componentClasses.ForEach([&hFile](const unsigned int& id, const FComponentInfo& info) {
		if (!info.isDefaultComponent && info.filepath.size() != 0)
		{
			hFile << "#include \"" << info.filepath << "\"" << Debug::endl;
		}
	});

	hFile << componentManager;
	hFile.Close();

	// Generate .cpp file
	CppCodeOStream cppFile(EditorApplication::sourceFilePath + "/DemoProjectComponentManager.cpp");
	cppFile << "#include \"DemoProjectComponentManager.h\"" << Debug::endl;
	cppFile << "#include \"Runtime/Containers/Algorithm.h\"" << Debug::endl;
	cppFile << "#include \"Runtime/Debug/Debug.h\"" << Debug::endl << Debug::endl;

	GenerateComponentManagerStartImpl(cppFile, componentManager);
	GenerateComponentManagerUpdateImpl(cppFile, componentManager);
	GenerateComponentManagerRenderSceneImpl(cppFile, componentManager);
	GenerateComponentManagerAddComponentImpl(cppFile, componentManager);
	GenerateComponentManagerGetComponentImpl(cppFile, componentManager);
	GenerateComponentManagerDeleteComponentImpl(cppFile, componentManager);
	GenerateComponentManagerGetComponentAtIndexImpl(cppFile, componentManager);
	GenerateComponentManagerOnGameObjectDeletedImpl(cppFile, componentManager);
	GenerateComponentManagerGetComponentPointersImpl(cppFile, componentManager);
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
	CppCodeOStream outFile(EditorApplication::sourceFilePath + "/DemoProjectSerializers.cpp");

	outFile << "#include \"DemoProject.h\"" << Debug::endl;
	outFile << "#include \"Runtime/Framework/BinaryParams.h\"" << Debug::endl;
	outFile << "#include \"Runtime/Framework/SceneLoader.h\"" << Debug::endl;
	outFile << Debug::endl;

	GenerateParamsListImpl(outFile);
	GenerateSetComponentParamsImpl(outFile);
	GenerateSetComponentBinaryParamsImpl(outFile);
	GenerateAddComponentToSceneImpl(outFile);
	GenerateSizeOfImpl(outFile);
	GenerateSerializedSizeOfImpl(outFile);
}

void CodeGenerator::GenerateTagFile()
{
	CppCodeOStream outFile(EditorApplication::sourceFilePath + "/DemoProjectTag.cpp");

	outFile << "#include <cstring>" << Debug::endl;
	outFile << "#include <string>" << Debug::endl << Debug::endl;

	outFile << "#ifndef EXPERIO_EDITOR" << Debug::endl;

	outFile << "unsigned short DefaultTagStringToNum(const char* string)" << Debug::endl;
	outFile << "{" << Debug::endl;

	ExperioEditor::GetTags().ForEach([&outFile](const uint16_t& key, const std::string& value) {
		outFile << "if(strcmp(string, \"" << value << "\")) { return " << std::to_string(key) << "; }" << Debug::endl;
	});

	outFile << "return 0;" << Debug::endl;
	outFile << "}" << Debug::endl;
	
	outFile << "std::string DefaultTagNumToString(unsigned short num)" << Debug::endl;
	outFile << "{" << Debug::endl;
	outFile << "switch(num)" << Debug::endl;
	outFile << "{" << Debug::endl;

	ExperioEditor::GetTags().ForEach([&outFile](const uint16_t& key, const std::string& value) {
		outFile << "case " << std::to_string(key) << ": " << "return \"" << value << "\";" << Debug::endl;
	});

	outFile << "}" << Debug::endl;
	outFile << "return \"Tag\";" << Debug::endl;
	outFile << "}" << Debug::endl;

	outFile << "#endif" << Debug::endl;
}

CodeClass CodeGenerator::GenerateComponentManagerClass()
{
	CodeClass codeClass("DemoProjectComponentManager");
	codeClass.inheritance.push_back("ComponentManager");
	codeClass.functions.reserve(12);

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
	
	// unsigned int classId, unsigned int index
	CodeFunction getComponentIndex("Component*", "GetComponentAtIndex");
	getComponentIndex.keywords = ECodeFunctionKeyword::Virtual;
	getComponentIndex.arguments.emplace_back("unsigned int", "classId", false);
	getComponentIndex.arguments.emplace_back("unsigned int", "index", false);
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

	getAllComponents.returnType = "void";
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

	codeClass.params.emplace_back("CameraSystem", "cameraSystem", ECodeAccessType::Public);

	return codeClass;
}

void CodeGenerator::GenerateComponentManagerStartImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "void " << codeClass.name << "::Start()" << Debug::endl << "{" << Debug::endl;
	cppFile << "cameraSystem.Start();" << Debug::endl;
	for (int i = 0; i < codeClass.params.size(); i++)
	{
		if (codeClass.params[i].type.find("std::vector") == 0)
		{
			cppFile << "PB_START(" << codeClass.params[i].name << ");" << Debug::endl;
		}
	}

	cppFile << "}" << Debug::endl << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerUpdateImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "void " << codeClass.name << "::Update()" << Debug::endl << "{" << Debug::endl;
	cppFile << "cameraSystem.Update();" << Debug::endl;

	std::vector<FComponentInfo> infos = EditorProject::componentClasses.GetValues();
	std::sort(infos.begin(), infos.end());

	for (size_t i = 0; i < infos.size(); i++)
	{
		if (!infos[i].isStandaloneComponent)
			continue;

		std::string paramName = LString::ToCamelCase(infos[i].name) + "Instances";
		cppFile << "PB_UPDATE(" << paramName << ");" << Debug::endl;
	}

	/*
	for (int i = 0; i < codeClass.params.size(); i++)
	{
		if (codeClass.params[i].type.find("std::vector") == 0)
		{
			cppFile << "PB_UPDATE(" << codeClass.params[i].name << ");" << Debug::endl;
		}
	}
	*/

	cppFile << "}" << Debug::endl << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerRenderSceneImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "void " << codeClass.name << "::RenderScene()" << Debug::endl << "{" << Debug::endl;
	cppFile << "cameraSystem.Update();" << Debug::endl;
	cppFile << "PB_UPDATE(meshComponentInstances);" << Debug::endl;
	cppFile << "PB_UPDATE(particleComponentInstances);" << Debug::endl;
	cppFile << "PB_UPDATE(billboardInstances);" << Debug::endl;
	cppFile << "PB_UPDATE(imageComponentInstances);" << Debug::endl;
	cppFile << "PB_UPDATE(textComponentInstances);" << Debug::endl;
	cppFile << "PB_UPDATE(progressBarInstances);" << Debug::endl;
	cppFile << "}" << Debug::endl << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerAddComponentImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "Component* " << codeClass.name << "::AddComponent(GameObject* gameObject, unsigned int classId)"
		<< Debug::endl << "{" << Debug::endl;
	cppFile << "switch(classId)" << Debug::endl << "{" << Debug::endl;
	cppFile << "case 100: return cameraSystem.AddComponent(gameObject);" << Debug::endl;
	
	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		if (info.isStandaloneComponent)
		{
			std::string paramName = LString::ToCamelCase(info.name) + "Instances";
			cppFile << "case " << std::to_string(id) << ": PB_ADD_COMPONENT(" << paramName << ");" << Debug::endl;
		}
	});

	cppFile << "}" << Debug::endl << "}" << Debug::endl << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerGetComponentImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "Component* " << codeClass.name << "::GetComponent(GameObject* gameObject, unsigned int classId)"
		<< Debug::endl << "{" << Debug::endl;
	cppFile << "switch(classId)" << Debug::endl << "{" << Debug::endl;
	cppFile << "case 100: return cameraSystem.GetComponent(gameObject);" << Debug::endl;

	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		if (info.isStandaloneComponent)
		{
			std::string paramName = LString::ToCamelCase(info.name) + "Instances";
			cppFile << "case " << std::to_string(id) << ": PB_GET_COMPONENT(" << paramName << ");" << Debug::endl;
		}
	});

	cppFile << "}" << Debug::endl << "}" << Debug::endl << Debug::endl;
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

	cppFile << "}" << Debug::endl << "}" << Debug::endl << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerDeleteComponentImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "void " << codeClass.name << "::DeleteComponent(GameObject* gameObject, unsigned int classId)"
		<< Debug::endl << "{" << Debug::endl;
	cppFile << "bool foundComponent = false;" << Debug::endl << Debug::endl;
	cppFile << "switch(classId)" << Debug::endl << "{" << Debug::endl;
	cppFile << "case 100: return cameraSystem.DeleteComponent(gameObject);" << Debug::endl;

	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		if (info.isStandaloneComponent)
		{
			std::string paramName = LString::ToCamelCase(info.name) + "Instances";
			cppFile << "case " << std::to_string(id) << ": PB_DELETE_COMPONENT(" << paramName << ");" << Debug::endl;
		}
	});

	cppFile << "}" << Debug::endl << "}" << Debug::endl << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerOnGameObjectDeletedImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "void " << codeClass.name << "::OnGameObjectDeleted(GameObject* gameObject)"
		<< Debug::endl << "{" << Debug::endl;
	cppFile << "bool foundComponent = false;" << Debug::endl << Debug::endl;
	cppFile << "cameraSystem.OnGameObjectDeleted(gameObject);" << Debug::endl;

	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		if (info.isStandaloneComponent)
		{
			std::string paramName = LString::ToCamelCase(info.name) + "Instances";
			cppFile << "PB_DELETE_COMPONENT(" << paramName << "); foundComponent = false;" << Debug::endl;
		}
	});

	cppFile << "}" << Debug::endl << Debug::endl;
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
	cppFile << "}" << Debug::endl << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerGetComponentPointersImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "std::vector<Component*> " << codeClass.name << "::GetComponentsInGameObject(GameObject * gameObject)"
		<< Debug::endl << "{" << Debug::endl;
	cppFile << "std::vector<Component*> returnVector;" << Debug::endl;
	cppFile << "Component* component;" << Debug::endl;
	cppFile << "returnVector.reserve(ComponentCount());" << Debug::endl << Debug::endl;

	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		cppFile << "PB_GET_COMPONENT_GAMEOBJECT(" << std::to_string(id) << ");" << Debug::endl;
	});

	cppFile << "return returnVector;" << Debug::endl;
	cppFile << "}" << Debug::endl << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerGetAllComponentsImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	// 0 args
	cppFile << "std::vector<Component*> " << codeClass.name << "::GetAllComponents()" << Debug::endl << "{" << Debug::endl;
	cppFile << "std::vector<Component*> vector;" << Debug::endl;
	cppFile << "vector.reserve(ComponentCount());" << Debug::endl;

	cppFile << "cameraSystem.GetAll(vector);" << Debug::endl;
	for (int i = 0; i < codeClass.params.size(); i++)
	{
		if (codeClass.params[i].type.find("std::vector") == 0)
		{
			cppFile << "PB_GET_ALL(" << codeClass.params[i].name << ");" << Debug::endl;
		}
	}

	cppFile << "return vector;" << Debug::endl;
	cppFile << "}" << Debug::endl << Debug::endl;

	// 2 arg
	cppFile << "void " << codeClass.name 
		<< "::GetAllComponents(std::vector<Component*>& components, std::vector<unsigned int>& componentIds)" 
		<< Debug::endl << "{" << Debug::endl;
	cppFile << "components.reserve(ComponentCount());" << Debug::endl;
	cppFile << "componentIds.reserve(ComponentCount());" << Debug::endl << Debug::endl;

	cppFile << "cameraSystem.GetAll(components);" << Debug::endl;
	cppFile << "Experio::Algorithm::AddNumOf(componentIds, (unsigned int)100, cameraSystem.Size());" << Debug::endl;
	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		if (info.isStandaloneComponent)
		{
			std::string paramName = LString::ToCamelCase(info.name) + "Instances";
			cppFile << "PB_GET_ALL_IDS(" << paramName << ", " << std::to_string(id) << ");" << Debug::endl;
		}
	});

	cppFile << "}" << Debug::endl << Debug::endl;

	// 3 arg
	cppFile << "void " << codeClass.name
		<< "::GetAllComponents(std::vector<Component*>& components, std::vector<unsigned int>& componentIds, uint8_t sceneIndex)"
		<< Debug::endl << "{" << Debug::endl;
	cppFile << "components.reserve(ComponentCount());" << Debug::endl;
	cppFile << "componentIds.reserve(ComponentCount());" << Debug::endl << Debug::endl;

	cppFile << "cameraSystem.GetAllOfScene(components, sceneIndex);" << Debug::endl;
	cppFile << "Experio::Algorithm::AddNumOf(componentIds, (unsigned int)100, cameraSystem.NumInScene(sceneIndex));" << Debug::endl;
	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		if (info.isStandaloneComponent)
		{
			std::string paramName = LString::ToCamelCase(info.name) + "Instances";
			cppFile << "PB_GET_ALL_SCENE_IDS(" << paramName << ", " << std::to_string(id) << ");" << Debug::endl;
		}
	});

	cppFile << "}" << Debug::endl << Debug::endl;
}

void CodeGenerator::GenerateComponentManagerCountImpl(CppCodeOStream & cppFile, const CodeClass & codeClass)
{
	cppFile << "unsigned int " << codeClass.name << "::ComponentCount() const" << Debug::endl << "{" << Debug::endl;
	cppFile << "return cameraSystem.Size()";
	for (int i = 0; i < codeClass.params.size(); i++)
	{
		if (codeClass.params[i].type.find("std::vector") == 0)
		{
			cppFile << " + " << codeClass.params[i].name << ".size()";
		}
	}
	cppFile << ";" << Debug::endl << "}" << Debug::endl;
}

void CodeGenerator::GenerateProjectHFile()
{
	CppCodeOStream hFile(EditorApplication::sourceFilePath + "/DemoProject.h");

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
	CodeFunction runProject("void", "RunProject");
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
	CppCodeOStream cppFile(EditorApplication::sourceFilePath + "/DemoProject.cpp");

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

void CodeGenerator::GenerateParamsListImpl(CppCodeOStream & cppFile)
{
	cppFile << "std::vector<std::string> GetParamsList(unsigned int classId)" << Debug::endl << "{" << Debug::endl;
	cppFile << "switch(classId)" << Debug::endl << "{" << Debug::endl;
	CodeProject& project = EditorProject::gameProject;
	EditorProject::componentClasses.ForEach([&cppFile, &project](const unsigned int& id, const FComponentInfo& info){
		CodeClass& codeClass = project.classes[project.FindIndexOfClass(info.name)];
		cppFile << "case " << std::to_string(id) << ": return std::vector<std::string>({ ";
		for (uint32_t i = 0; i < codeClass.params.size(); i++)
		{
			cppFile << "\"" << codeClass.params[i].name << "\"";

			if (i < codeClass.params.size() - 1) cppFile << ", ";
		}
		cppFile << "});" << Debug::endl;
	});
	cppFile << "}" << Debug::endl << "return std::vector<std::string>();" << Debug::endl << "}" << Debug::endl << Debug::endl;
}

void CodeGenerator::GenerateSetComponentParamsImpl(CppCodeOStream & cppFile)
{
	cppFile << "template<class T> void SetComponentParams(std::vector<std::string> params, T* component) { }" 
		<< Debug::endl << Debug::endl;

	CodeProject& project = EditorProject::gameProject;
	EditorProject::componentClasses.ForEach([&cppFile, &project](const unsigned int& id, const FComponentInfo& info) {
		cppFile << "template<> void SetComponentParams(std::vector<std::string> params, "
			<< info.name << "* component)" << Debug::endl << "{" << Debug::endl;

		CodeClass& codeClass = project.classes[project.FindIndexOfClass(info.name)];
		LSerializationOperations::GenerateParser(codeClass, project, cppFile);
		cppFile << "}" << Debug::endl << Debug::endl;
	});
}

void CodeGenerator::GenerateSetComponentBinaryParamsImpl(CppCodeOStream & cppFile)
{
	cppFile << "template<class T> void SetComponentBinaryParams(void* data, T* component) { }"
		<< Debug::endl << Debug::endl;

	CodeProject& project = EditorProject::gameProject;
	EditorProject::componentClasses.ForEach([&cppFile, &project](const unsigned int& id, const FComponentInfo& info) {
		cppFile << "template<> void SetComponentBinaryParams(void* data, "
			<< info.name << "* component)" << Debug::endl << "{" << Debug::endl;

		CodeClass& codeClass = project.classes[project.FindIndexOfClass(info.name)];
		LSerializationOperations::GenerateBinaryParser(codeClass, project, cppFile);
		cppFile << "}" << Debug::endl << Debug::endl;
	});
}

void CodeGenerator::GenerateAddComponentToSceneImpl(CppCodeOStream & cppFile)
{
	cppFile << "void AddComponentToScene(unsigned int classId, std::vector<std::string> params, "
		<< "GameObject* gameObject, uint8_t sceneId)" << Debug::endl << "{" << Debug::endl;
	cppFile << "switch(classId)" << Debug::endl << "{" << Debug::endl;
	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		cppFile << "case " << std::to_string(id) << ": { PB_EMPLACE_COMPONENT(" << info.name
			<< ", classId); PB_START_COMPONENT(); } break;" << Debug::endl;
	});
	cppFile << "}" << Debug::endl << "}" << Debug::endl << Debug::endl;

	cppFile << "void AddComponentToScene(unsigned int classId, void* params, size_t paramSize, "
		<< "GameObject* gameObject, uint8_t sceneId)" << Debug::endl << "{" << Debug::endl;
	cppFile << "switch(classId)" << Debug::endl << "{" << Debug::endl;
	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		cppFile << "case " << std::to_string(id) << ": { PB_EMPLACE_BINARY_COMPONENT(" << info.name
			<< ", classId); PB_START_COMPONENT(); } break;" << Debug::endl;
	});
	cppFile << "}" << Debug::endl << "}" << Debug::endl << Debug::endl;
}

void CodeGenerator::GenerateSizeOfImpl(CppCodeOStream & cppFile)
{
	cppFile << "size_t SizeOfComponent(unsigned int classId)" << Debug::endl << "{" << Debug::endl;
	cppFile << "switch(classId)" << Debug::endl << "{" << Debug::endl;
	EditorProject::componentClasses.ForEach([&cppFile](const unsigned int& id, const FComponentInfo& info) {
		cppFile << "case " << std::to_string(id) << ": return sizeof(" << info.name << ");" << Debug::endl;
	});
	cppFile << "}" << Debug::endl << "return 0;" << Debug::endl << "}" << Debug::endl << Debug::endl;
}

void CodeGenerator::GenerateSerializedSizeOfImpl(CppCodeOStream & cppFile)
{
	cppFile << "size_t SerializedSizeOfComponent(unsigned int classId)" << Debug::endl << "{" << Debug::endl;
	cppFile << "switch(classId)" << Debug::endl << "{" << Debug::endl;

	CodeProject& project = EditorProject::gameProject;
	EditorProject::componentClasses.ForEach([&cppFile, &project](const unsigned int& id, const FComponentInfo& info) {
		CodeClass& codeClass = project.classes[project.FindIndexOfClass(info.name)];
		size_t serializedSizeOf = LSerializationOperations::SerializedSizeOf(codeClass, project, ECodingLanguage::CPlusPlus);
		cppFile << "case " << std::to_string(id) << ": return " << std::to_string(serializedSizeOf) << ";" << Debug::endl;
	});
	cppFile << "}" << Debug::endl << "return 0;" << Debug::endl << "}" << Debug::endl << Debug::endl;
}
