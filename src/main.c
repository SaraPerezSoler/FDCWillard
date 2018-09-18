/**
 * @file
 * @brief Main file.
 */

#include "FDC_GameEngine.h"
#include "FDC_Error.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	FDC_GameEngine engine;

	FOREACH_ERROR(e)
	{
		printf("%s: %s\n", e->id, e->name);
	}

	FDC_GameEngine_mainLoop(&engine);
}
