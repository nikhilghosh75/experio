#include "ImportScripts.h"
#include "../Core/DialogBox.h"
#include "../Framework/SaveParams.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Framework/Params.h"
#include "Runtime/Math/FVector3.h"
#include <fstream>
#include <sstream>

enum class EMTLMaterialType
{
	Colored,
	Standard,
	TransparentColored,
	TransparentTextured,
	PBRColored,
	PBRTextured,
	Emissive,
	EmissiveTextured
};

std::vector<EMTLMaterialType> GetMaterialTypes(const std::string& filepath)
{
	EMTLMaterialType currentMaterialType = EMTLMaterialType::Colored;
	std::vector<EMTLMaterialType> materialTypes;

	std::string str;
	std::ifstream inFile(filepath);

	while (inFile >> str)
	{
		if (str == "newmtl")
		{
			materialTypes.push_back(currentMaterialType);
			currentMaterialType = EMTLMaterialType::Colored;
			inFile >> str;
		}
		else if (str == "map_Ka" || str == "map_Ks" || str == "map_Ns")
		{
			if (currentMaterialType == EMTLMaterialType::Colored)
				currentMaterialType = EMTLMaterialType::Standard;
			else if (currentMaterialType == EMTLMaterialType::TransparentColored)
				currentMaterialType = EMTLMaterialType::TransparentTextured;
			inFile >> str;
		}
		else if (str == "d" || str == "Tr")
		{
			if (currentMaterialType == EMTLMaterialType::Colored)
				currentMaterialType = EMTLMaterialType::TransparentColored;
			else if (currentMaterialType == EMTLMaterialType::Standard)
				currentMaterialType = EMTLMaterialType::TransparentTextured;
			inFile >> str;
		}
		else if (str == "Pr" || str == "Pm" || str == "Ps" || str == "Pc" || str == "Pcr")
		{
			currentMaterialType = EMTLMaterialType::PBRColored;
		}
		else if (str == "map_Pr" || str == "map_Pm" || str == "map_Ps")
		{
			currentMaterialType = EMTLMaterialType::PBRTextured;
		}
		else if (str == "Ke")
		{
			currentMaterialType = EMTLMaterialType::Emissive;
		}
		else if (str == "map_Ke")
		{
			currentMaterialType = EMTLMaterialType::EmissiveTextured;
		}
	}
	
	materialTypes.push_back(currentMaterialType);
	return materialTypes;
}

std::string GetNewMaterialPath(const std::string& directory, const std::string& materialName)
{
	std::stringstream ss;
	ss << directory << "/" << materialName << ".material";
	return ss.str();
}

std::string GetMaterialTypeShader(EMTLMaterialType materialType)
{
	switch (materialType)
	{
	case EMTLMaterialType::Colored: return "?Standard?/Shaders/Colored.shader";
	case EMTLMaterialType::Emissive: return "?Standard?/Shaders/EmissiveColored.shader";
	case EMTLMaterialType::EmissiveTextured: return "?Standard?/Shaders/Emissive.shader";
	case EMTLMaterialType::PBRColored: return "?Standard?/Shaders/PBRColored.shader";
	case EMTLMaterialType::PBRTextured: return "?Standard?/Shaders/PBR.shader";
	case EMTLMaterialType::Standard: return "?Standard?/Shaders/Basic.shader";
	case EMTLMaterialType::TransparentColored: return "?Standard?/Shaders/TransparentColored.shader";
	case EMTLMaterialType::TransparentTextured: return "?Standard?/Shaders/Transparent.shader";
	}
	return "";
}

void ConvertMaterials(const std::string& filepath, const std::vector<EMTLMaterialType>& materialTypes)
{
	int currentIndex = -1;

	std::string directory = LFileOperations::GetDirectory(filepath);
	
	std::string str;
	std::ifstream inFile(filepath);
	bool fileOpened = false;
	std::ofstream outFile;

	char temp[256];

	while (inFile >> str)
	{
		if (str[0] == '#')
		{
			inFile.getline(temp, 256);
			continue;
		}
		else if (str == "newmtl")
		{
			inFile >> str;
			if(fileOpened) outFile.close();
			outFile.open(GetNewMaterialPath(directory, str));
			currentIndex++;

			outFile << "MATERIAL" << std::endl;
			outFile << "Type: " << "MeshMaterial" << std::endl;
			outFile << "Shader: " << GetMaterialTypeShader(materialTypes[currentIndex]) << std::endl;
		}
		else if (str == "Ka")
		{
			FVector3 v;
			inFile >> v.x >> v.y >> v.z;
			outFile << "ambient: ";
			SaveVector3(v, outFile);
		}
		else if (str == "Kd")
		{
			FVector3 v;
			inFile >> v.x >> v.y >> v.z;
			outFile << "diffuse: ";
			SaveVector3(v, outFile);
		}
		else if (str == "Ks")
		{
			FVector3 v;
			inFile >> v.x >> v.y >> v.z;
			outFile << "specular: ";
			SaveVector3(v, outFile);
		}
		else if (str == "Ns")
		{
			float exponent;
			inFile >> exponent;
			outFile << "specularExponent: ";
			SaveFloat(exponent, outFile);
		}
		else if (str == "d")
		{
			float opacity;
			inFile >> opacity;
			outFile << "opacity: ";
			SaveFloat(opacity, outFile);
		}
		else if (str == "Tr")
		{
			float opacity;
			inFile >> opacity;
			outFile << "opacity: ";
			SaveFloat(1 - opacity, outFile);
		}
		else if (str == "Tf")
		{
			FVector3 v;
			inFile >> v.x >> v.y >> v.z;
			outFile << "filterColor: ";
			SaveVector3(v, outFile);
		}
		else if (str == "Ni")
		{
			float refraction;
			inFile >> refraction;
			outFile << "refraction: ";
			SaveFloat(refraction, outFile);
		}
		else if (str == "map_Ka")
		{
			inFile >> str;
			outFile << "ambient: " << str;
		}
		else if (str == "map_Ks")
		{
			inFile >> str;
			outFile << "specular:" << str;
		}
		else if (str == "map_bump" || str == "bump")
		{
			inFile >> str;
			outFile << "normal: " << str;
		}
		else if (str == "disp")
		{
			inFile >> str;
			outFile << "displacement: " << str;
		}
		else if (str == "bump")
		{
			inFile >> str;
			outFile << "bump: " << str;
		}
		else if (str == "Pr")
		{
			float roughness;
			inFile >> roughness;
			outFile << "roughness: ";
			SaveFloat(roughness, outFile);
		}
		else if (str == "Pm")
		{
			float metallic;
			inFile >> metallic;
			outFile << "metallic: ";
			SaveFloat(metallic, outFile);
		}
		else if (str == "Ps")
		{
			float sheen;
			inFile >> sheen;
			outFile << "sheen: ";
			SaveFloat(sheen, outFile);
		}
		else if (str == "map_Pr")
		{
			inFile >> str;
			outFile << "roughness: " << str;
		}
		else if (str == "map_Pm")
		{
			inFile >> str;
			outFile << "metallic: " << str;
		}
		else if (str == "map_Ps")
		{
			inFile >> str;
			outFile << "sheen: " << str;
		}
		outFile << std::endl;
	}
}

EImportHandlerResult ImportMTL(FImportInfo info)
{
	if (!LFileOperations::DoesFileHaveExtension(info.filepath, "mtl")) return EImportHandlerResult::NotHandled;

	if (EditorDialogBox::YesNo("Convert MTL", "Convert MTL Files into Material files") == EDialogBoxValue::No)
		return EImportHandlerResult::Handled;

	std::vector<EMTLMaterialType> materialTypes = GetMaterialTypes(info.filepath);
	ConvertMaterials(info.filepath, materialTypes);

	return EImportHandlerResult::Handled;
}

IMPORT_FUNCTION(ImportMTL);