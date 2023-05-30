#include "stdafx.h"
#include "Engine.h"

int main()
{
	Engine engine;
	engine.request(STATE_START);
	engine.start();

	return EXIT_SUCCESS;
}
