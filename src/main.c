/**
 * @file
 * @brief Main file.
 */

#include "FDC_GameEngine.h"
#include "FDC_Error.h"
#include "FDC_Console.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	FDC_GameEngine engine;
	FDC_Console console;

	FDC_FOREACH_ERROR(e)
	{
		printf("%s: %s\n", e->id, e->name);
	}

	FDC_Console_init(&console);

	printf("%s", FDC_error_message.buffer);

	FDC_ConsoleBuffer_setCursorPosition(NULL, 0, 0);
	FDC_GameEngine_mainLoop(&engine);
}
