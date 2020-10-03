#include "Project.h"
#include "Component.h"
#include "../Time/GameTime.h"
#include "../../ThirdParty/Nameof/nameof.hpp"

extern std::string projectName;

extern unsigned short DefaultTagStringToNum(const char* string);

extern std::string DefaultTagNumToString(unsigned short num);

template <class T>
extern unsigned int DefaultClassTypeToInt();

extern unsigned int DefaultClassStringToInt(std::string name);

template <class T>
extern std::string DefaultClassTypeToString();

bool Project::inEditor = false;
std::string Project::projectName = projectName;

ComponentManager* Project::componentManager;
MaterialManager* Project::materialManager;

void Project::BeginFrame()
{
	GameTime::OnBeginFrame();
}

void Project::EndFrame()
{
	GameTime::OnEndFrame();
}

void Project::StartGame()
{
	GameTime::StartGame();
}

unsigned short Project::TagStringToNum(const char * string)
{
	return DefaultTagStringToNum(string);
}

std::string Project::TagNumToString(unsigned short num)
{
	return DefaultTagNumToString(num);
}

template<class T>
unsigned int Project::ClassTypeToInt()
{
#ifdef EXPERIO_EDITOR
	return DefaultClassStringToInt(NAMEOF_TYPE(T));
#else
	return DefaultClassTypeToInt<T>();
#endif // EXPERIO_EDITOR
}

template<>
unsigned int Project::ClassTypeToInt<TestComponent>()
{
	return 2;
}

template<class T>
std::string Project::ClassTypeToString()
{
	return DefaultClassTypeToString<T>();
}
