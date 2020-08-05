#include "Project.h"
#include "Component.h"

extern std::string projectName;

extern unsigned short DefaultTagStringToNum(const char* string);

extern std::string DefaultTagNumToString(unsigned short num);

template <class T>
extern unsigned int DefaultClassTypeToInt();

template <class T>
extern std::string DefaultClassTypeToString();

std::string Project::projectName = projectName;

ComponentManager* Project::componentManager;

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
	return DefaultClassTypeToInt<T>();
}

template<>
unsigned int Project::ClassTypeToInt<TestComponent>()
{
	return DefaultClassTypeToInt<TestComponent>();
}

template<class T>
std::string Project::ClassTypeToString()
{
	return DefaultClassTypeToString<T>();
}
