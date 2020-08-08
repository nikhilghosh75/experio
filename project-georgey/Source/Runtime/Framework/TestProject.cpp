#include <string>
#include "Component.h"

std::string projectName = "Test Project";

unsigned short DefaultTagStringToNum(const char* string)
{
	if (strcmp(string, "Player"))
	{
		return 1;
	}
	if (strcmp(string, "Enemy"))
	{
		return 2;
	}
	return 0;
}

std::string DefaultTagNumToString(unsigned short num)
{
	switch (num)
	{
	case 1:
		return "Player";
	case 2:
		return "Enemy";
	}
	return "";
}

class MeshComponent;
class ParticleSystem;
class Billboard;
class TextComponent;

template <class T>
unsigned int DefaultClassTypeToInt()
{
	return 0;
}

template<>
unsigned int DefaultClassTypeToInt<TestComponent>()
{
	return 2;
}

template<> unsigned int DefaultClassTypeToInt<MeshComponent>() { return 101; }
template<> unsigned int DefaultClassTypeToInt<ParticleSystem>() { return 102; }
template<> unsigned int DefaultClassTypeToInt<Billboard>() { return 103; }
template<> unsigned int DefaultClassTypeToInt<TextComponent>() { return 104; }