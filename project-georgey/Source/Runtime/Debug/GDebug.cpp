#define console

#include "GDebug.h"

#ifdef console
#include <iostream>
using namespace std;
#endif

void GDebug::Log(string s)
{
#ifdef console
	cout << s;
#endif
}
