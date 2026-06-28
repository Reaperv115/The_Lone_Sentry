#include "Application.h"

int main()
{
	auto app = Engine::CreateUnique<Engine::Application>();
	app->Run();

	return 0;
}