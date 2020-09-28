#include "EditorProject.h"

THashtable<unsigned int, std::string> EditorProject::classes;

unsigned int DefaultClassStringToInt(std::string name)
{
	unsigned int classId;
	if (EditorProject::classes.Find(name, classId))
	{
		return classId;
	}
	return 0;
}

void EditorProject::TempSetup()
{
	EditorProject::classes.Insert(100, "VirtualCamera");
	EditorProject::classes.Insert(101, "MeshComponent");
	EditorProject::classes.Insert(102, "ParticleSystem");
	EditorProject::classes.Insert(103, "Billboard");
	EditorProject::classes.Insert(104, "TextComponent");
}
