#include "GAmber.h"

GAmber::GAmber()
{

}

GAmber::~GAmber()
{

}

GApplication* CreateApplication()
{
	return new GAmber();
}
