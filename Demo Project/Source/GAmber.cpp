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

int main(int argc, char** argv)
{
	GApplication* app = CreateApplication();
	app->Run();
	delete app;
}
