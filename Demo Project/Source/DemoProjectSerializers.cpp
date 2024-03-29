#include "DemoProject.h"
#include "Runtime/Framework/BinaryParams.h"
#include "Runtime/Framework/SceneLoader.h"

std::vector<std::string> GetParamsList(unsigned int classId)
{
	switch(classId)
	{
		case 104: return std::vector<std::string>({ "margins", "fontSize", "font", "text", "color", "horizontalWrapMode", "verticalWrapMode", "horizontalAlignment", "verticalAlignment", "spacing", "shader", "text"});
		case 112: return std::vector<std::string>({ "margins"});
		case 1024: return std::vector<std::string>({ "isActive = false", "isAccelerating = false", "acceleration", "topSpeed"});
		case 105: return std::vector<std::string>({ "texture", "tint"});
		case 113: return std::vector<std::string>({ "margins"});
		case 106: return std::vector<std::string>({ "minValue", "maxValue", "value", "backgroundColor", "barColor", "shader", "mode"});
		case 114: return std::vector<std::string>({ "margins"});
		case 107: return std::vector<std::string>({ "roundedPixels", "color", "texture"});
		case 100: return std::vector<std::string>({ "priority", "fieldOfView", "nearClipPlane", "farClipPlane"});
		case 108: return std::vector<std::string>({ "defaultColor", "hoveredColor", "activeColor"});
		case 101: return std::vector<std::string>({ "material", "meshData", "isVisible"});
		case 109: return std::vector<std::string>({ "offColor", "onColor", "isOn"});
		case 102: return std::vector<std::string>({ });
		case 110: return std::vector<std::string>({ "value"});
		case 103: return std::vector<std::string>({ "billboardTexture", "sizeType", "orientation", "billboardSize"});
		case 111: return std::vector<std::string>({ "enableAlpha", "enableNumeric", "enableUppercase", "enableLowercase"});
	}
	return std::vector<std::string>();
}

template<class T> void SetComponentParams(std::vector<std::string> params, T* component) { }

template<> void SetComponentParams(std::vector<std::string> params, TextComponent* component)
{
	component->margins = ParseFloat(params[0]);
	component->fontSize = ParseInt(params[1]);
	component->font = ParseFont(params[2]);
	component->text = ParseString(params[3]);
	component->color = ParseColor(params[4]);
	component->horizontalWrapMode = (EHorizontalWrapMode)ParseUByte(params[5]);
	component->verticalWrapMode = (EVerticalWrapMode)ParseUByte(params[6]);
	component->horizontalAlignment = (EHorizontalAlignment)ParseUByte(params[7]);
	component->verticalAlignment = (EVerticalAlignment)ParseUByte(params[8]);
	component->spacing = ParseFloat(params[9]);
	component->shader = ParseShader(params[10]);
	component->text = ParseString(params[11]);
}

template<> void SetComponentParams(std::vector<std::string> params, HorizontalLayout* component)
{
	component->margins = ParseFloat(params[0]);
}

template<> void SetComponentParams(std::vector<std::string> params, Spaceship* component)
{
	component->acceleration = ParseFloat(params[0]);
	component->topSpeed = ParseFloat(params[1]);
}

template<> void SetComponentParams(std::vector<std::string> params, ImageComponent* component)
{
	component->texture = ParseTexture(params[0]);
	component->tint = ParseColor(params[1]);
}

template<> void SetComponentParams(std::vector<std::string> params, VerticalLayout* component)
{
	component->margins = ParseFloat(params[0]);
}

template<> void SetComponentParams(std::vector<std::string> params, ProgressBar* component)
{
	component->minValue = ParseFloat(params[0]);
	component->maxValue = ParseFloat(params[1]);
	component->value = ParseFloat(params[2]);
	component->backgroundColor = ParseColor(params[3]);
	component->barColor = ParseColor(params[4]);
	component->shader = ParseShader(params[5]);
	component->mode = (EProgressBarMode)ParseUByte(params[6]);
}

template<> void SetComponentParams(std::vector<std::string> params, GridLayout* component)
{
	component->margins = ParseFloat(params[0]);
}

template<> void SetComponentParams(std::vector<std::string> params, Panel* component)
{
	component->roundedPixels = ParseFloat(params[0]);
	component->color = ParseColor(params[1]);
	component->texture = ParseTexture(params[2]);
}

template<> void SetComponentParams(std::vector<std::string> params, VirtualCamera* component)
{
	component->priority = ParseFloat(params[0]);
	component->fieldOfView = ParseFloat(params[1]);
	component->nearClipPlane = ParseFloat(params[2]);
	component->farClipPlane = ParseFloat(params[3]);
}

template<> void SetComponentParams(std::vector<std::string> params, Button* component)
{
	component->defaultColor = ParseColor(params[0]);
	component->hoveredColor = ParseColor(params[1]);
	component->activeColor = ParseColor(params[2]);
}

template<> void SetComponentParams(std::vector<std::string> params, MeshComponent* component)
{
	component->material = (MeshMaterial*)ParseMaterial(params[0]);
	component->meshData = ParseMesh(params[1]);
	component->isVisible = ParseBool(params[2]);
}

template<> void SetComponentParams(std::vector<std::string> params, CheckBox* component)
{
	component->offColor = ParseColor(params[0]);
	component->onColor = ParseColor(params[1]);
	component->isOn = ParseBool(params[2]);
}

template<> void SetComponentParams(std::vector<std::string> params, ParticleComponent* component)
{
}

template<> void SetComponentParams(std::vector<std::string> params, Slider* component)
{
	component->value = ParseFloat(params[0]);
}

template<> void SetComponentParams(std::vector<std::string> params, Billboard* component)
{
	component->billboardTexture = ParseTexture(params[0]);
	component->sizeType = (EBillboardSizeType)ParseUByte(params[1]);
	component->orientation = (EBilboardOrientation)ParseUByte(params[2]);
	component->billboardSize = ParseVector2(params[3]);
}

template<> void SetComponentParams(std::vector<std::string> params, InputText* component)
{
	component->enableAlpha = ParseBool(params[0]);
	component->enableNumeric = ParseBool(params[1]);
	component->enableUppercase = ParseBool(params[2]);
	component->enableLowercase = ParseBool(params[3]);
}

template<class T> void SetComponentBinaryParams(void* data, T* component) { }

template<> void SetComponentBinaryParams(void* data, TextComponent* component)
{
	component->margins = BinaryParseFloat((void*)((char*)data + 0));
	component->fontSize = BinaryParseInt((void*)((char*)data + 4));
	component->font = BinaryParseFont((void*)((char*)data + 8));
	component->text = BinaryParseString((void*)((char*)data + 12));
	component->color = BinaryParseColor((void*)((char*)data + 12));
	component->horizontalWrapMode = (EHorizontalWrapMode)BinaryParseUByte((void*)((char*)data + 28));
	component->verticalWrapMode = (EVerticalWrapMode)BinaryParseUByte((void*)((char*)data + 29));
	component->horizontalAlignment = (EHorizontalAlignment)BinaryParseUByte((void*)((char*)data + 30));
	component->verticalAlignment = (EVerticalAlignment)BinaryParseUByte((void*)((char*)data + 31));
	component->spacing = BinaryParseFloat((void*)((char*)data + 32));
	component->shader = BinaryParseShader((void*)((char*)data + 36));
	component->text = BinaryParseString((void*)((char*)data + 40));
}

template<> void SetComponentBinaryParams(void* data, HorizontalLayout* component)
{
	component->margins = BinaryParseFloat((void*)((char*)data + 0));
}

template<> void SetComponentBinaryParams(void* data, Spaceship* component)
{
	component->acceleration = BinaryParseFloat((void*)((char*)data + 0));
	component->topSpeed = BinaryParseFloat((void*)((char*)data + 4));
}

template<> void SetComponentBinaryParams(void* data, ImageComponent* component)
{
	component->texture = BinaryParseTexture((void*)((char*)data + 0));
	component->tint = BinaryParseColor((void*)((char*)data + 4));
}

template<> void SetComponentBinaryParams(void* data, VerticalLayout* component)
{
	component->margins = BinaryParseFloat((void*)((char*)data + 0));
}

template<> void SetComponentBinaryParams(void* data, ProgressBar* component)
{
	component->minValue = BinaryParseFloat((void*)((char*)data + 0));
	component->maxValue = BinaryParseFloat((void*)((char*)data + 4));
	component->value = BinaryParseFloat((void*)((char*)data + 8));
	component->backgroundColor = BinaryParseColor((void*)((char*)data + 12));
	component->barColor = BinaryParseColor((void*)((char*)data + 28));
	component->shader = BinaryParseShader((void*)((char*)data + 44));
	component->mode = (EProgressBarMode)BinaryParseUByte((void*)((char*)data + 48));
}

template<> void SetComponentBinaryParams(void* data, GridLayout* component)
{
	component->margins = BinaryParseFloat((void*)((char*)data + 0));
}

template<> void SetComponentBinaryParams(void* data, Panel* component)
{
	component->roundedPixels = BinaryParseFloat((void*)((char*)data + 0));
	component->color = BinaryParseColor((void*)((char*)data + 4));
	component->texture = BinaryParseTexture((void*)((char*)data + 20));
}

template<> void SetComponentBinaryParams(void* data, VirtualCamera* component)
{
	component->priority = BinaryParseFloat((void*)((char*)data + 0));
	component->fieldOfView = BinaryParseFloat((void*)((char*)data + 4));
	component->nearClipPlane = BinaryParseFloat((void*)((char*)data + 8));
	component->farClipPlane = BinaryParseFloat((void*)((char*)data + 12));
}

template<> void SetComponentBinaryParams(void* data, Button* component)
{
	component->defaultColor = BinaryParseColor((void*)((char*)data + 0));
	component->hoveredColor = BinaryParseColor((void*)((char*)data + 16));
	component->activeColor = BinaryParseColor((void*)((char*)data + 32));
}

template<> void SetComponentBinaryParams(void* data, MeshComponent* component)
{
	component->material = (MeshMaterial*)BinaryParseMaterial((void*)((char*)data + 0));
	component->meshData = BinaryParseMesh((void*)((char*)data + 4));
	component->isVisible = BinaryParseBool((void*)((char*)data + 8));
}

template<> void SetComponentBinaryParams(void* data, CheckBox* component)
{
	component->offColor = BinaryParseColor((void*)((char*)data + 0));
	component->onColor = BinaryParseColor((void*)((char*)data + 16));
	component->isOn = BinaryParseBool((void*)((char*)data + 32));
}

template<> void SetComponentBinaryParams(void* data, ParticleComponent* component)
{
}

template<> void SetComponentBinaryParams(void* data, Slider* component)
{
	component->value = BinaryParseFloat((void*)((char*)data + 0));
}

template<> void SetComponentBinaryParams(void* data, Billboard* component)
{
	component->billboardTexture = BinaryParseTexture((void*)((char*)data + 0));
	component->sizeType = (EBillboardSizeType)BinaryParseUByte((void*)((char*)data + 4));
	component->orientation = (EBilboardOrientation)BinaryParseUByte((void*)((char*)data + 5));
	component->billboardSize = BinaryParseVector2((void*)((char*)data + 6));
}

template<> void SetComponentBinaryParams(void* data, InputText* component)
{
	component->enableAlpha = BinaryParseBool((void*)((char*)data + 0));
	component->enableNumeric = BinaryParseBool((void*)((char*)data + 1));
	component->enableUppercase = BinaryParseBool((void*)((char*)data + 2));
	component->enableLowercase = BinaryParseBool((void*)((char*)data + 3));
}

void AddComponentToScene(unsigned int classId, std::vector<std::string> params, GameObject* gameObject, uint8_t sceneId)
{
	switch(classId)
	{
		case 104: { PB_EMPLACE_COMPONENT(TextComponent, classId); PB_START_COMPONENT(); } break;
		case 112: { PB_EMPLACE_COMPONENT(HorizontalLayout, classId); PB_START_COMPONENT(); } break;
		case 1024: { PB_EMPLACE_COMPONENT(Spaceship, classId); PB_START_COMPONENT(); } break;
		case 105: { PB_EMPLACE_COMPONENT(ImageComponent, classId); PB_START_COMPONENT(); } break;
		case 113: { PB_EMPLACE_COMPONENT(VerticalLayout, classId); PB_START_COMPONENT(); } break;
		case 106: { PB_EMPLACE_COMPONENT(ProgressBar, classId); PB_START_COMPONENT(); } break;
		case 114: { PB_EMPLACE_COMPONENT(GridLayout, classId); PB_START_COMPONENT(); } break;
		case 107: { PB_EMPLACE_COMPONENT(Panel, classId); PB_START_COMPONENT(); } break;
		case 100: { PB_EMPLACE_COMPONENT(VirtualCamera, classId); PB_START_COMPONENT(); } break;
		case 108: { PB_EMPLACE_COMPONENT(Button, classId); PB_START_COMPONENT(); } break;
		case 101: { PB_EMPLACE_COMPONENT(MeshComponent, classId); PB_START_COMPONENT(); } break;
		case 109: { PB_EMPLACE_COMPONENT(CheckBox, classId); PB_START_COMPONENT(); } break;
		case 102: { PB_EMPLACE_COMPONENT(ParticleComponent, classId); PB_START_COMPONENT(); } break;
		case 110: { PB_EMPLACE_COMPONENT(Slider, classId); PB_START_COMPONENT(); } break;
		case 103: { PB_EMPLACE_COMPONENT(Billboard, classId); PB_START_COMPONENT(); } break;
		case 111: { PB_EMPLACE_COMPONENT(InputText, classId); PB_START_COMPONENT(); } break;
	}
}

void AddComponentToScene(unsigned int classId, void* params, size_t paramSize, GameObject* gameObject, uint8_t sceneId)
{
	switch(classId)
	{
		case 104: { PB_EMPLACE_BINARY_COMPONENT(TextComponent, classId); PB_START_COMPONENT(); } break;
		case 112: { PB_EMPLACE_BINARY_COMPONENT(HorizontalLayout, classId); PB_START_COMPONENT(); } break;
		case 1024: { PB_EMPLACE_BINARY_COMPONENT(Spaceship, classId); PB_START_COMPONENT(); } break;
		case 105: { PB_EMPLACE_BINARY_COMPONENT(ImageComponent, classId); PB_START_COMPONENT(); } break;
		case 113: { PB_EMPLACE_BINARY_COMPONENT(VerticalLayout, classId); PB_START_COMPONENT(); } break;
		case 106: { PB_EMPLACE_BINARY_COMPONENT(ProgressBar, classId); PB_START_COMPONENT(); } break;
		case 114: { PB_EMPLACE_BINARY_COMPONENT(GridLayout, classId); PB_START_COMPONENT(); } break;
		case 107: { PB_EMPLACE_BINARY_COMPONENT(Panel, classId); PB_START_COMPONENT(); } break;
		case 100: { PB_EMPLACE_BINARY_COMPONENT(VirtualCamera, classId); PB_START_COMPONENT(); } break;
		case 108: { PB_EMPLACE_BINARY_COMPONENT(Button, classId); PB_START_COMPONENT(); } break;
		case 101: { PB_EMPLACE_BINARY_COMPONENT(MeshComponent, classId); PB_START_COMPONENT(); } break;
		case 109: { PB_EMPLACE_BINARY_COMPONENT(CheckBox, classId); PB_START_COMPONENT(); } break;
		case 102: { PB_EMPLACE_BINARY_COMPONENT(ParticleComponent, classId); PB_START_COMPONENT(); } break;
		case 110: { PB_EMPLACE_BINARY_COMPONENT(Slider, classId); PB_START_COMPONENT(); } break;
		case 103: { PB_EMPLACE_BINARY_COMPONENT(Billboard, classId); PB_START_COMPONENT(); } break;
		case 111: { PB_EMPLACE_BINARY_COMPONENT(InputText, classId); PB_START_COMPONENT(); } break;
	}
}

size_t SizeOfComponent(unsigned int classId)
{
	switch(classId)
	{
		case 104: return sizeof(TextComponent);
		case 112: return sizeof(HorizontalLayout);
		case 1024: return sizeof(Spaceship);
		case 105: return sizeof(ImageComponent);
		case 113: return sizeof(VerticalLayout);
		case 106: return sizeof(ProgressBar);
		case 114: return sizeof(GridLayout);
		case 107: return sizeof(Panel);
		case 100: return sizeof(VirtualCamera);
		case 108: return sizeof(Button);
		case 101: return sizeof(MeshComponent);
		case 109: return sizeof(CheckBox);
		case 102: return sizeof(ParticleComponent);
		case 110: return sizeof(Slider);
		case 103: return sizeof(Billboard);
		case 111: return sizeof(InputText);
	}
	return 0;
}

size_t SerializedSizeOfComponent(unsigned int classId)
{
	switch(classId)
	{
		case 104: return 48;
		case 112: return 4;
		case 1024: return 8;
		case 105: return 20;
		case 113: return 4;
		case 106: return 45;
		case 114: return 4;
		case 107: return 24;
		case 100: return 16;
		case 108: return 48;
		case 101: return 9;
		case 109: return 33;
		case 102: return 0;
		case 110: return 4;
		case 103: return 14;
		case 111: return 4;
	}
	return 0;
}

