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
	FDC_ConsoleBufferVirtual console_buffer_virtual;
	FDC_Console console;

	FDC_FOREACH_ERROR(e)
	{
		printf("%s: %s\n", e->id, e->name);
	}

	FDC_Console_init(&console);

	FDC_ConsoleBufferVirtual_init(&console_buffer_virtual, 10, 10);



	FDC_Error error = FDC_ConsoleBufferVirtual_writeToConsole(&console_buffer_virtual, &console);
	if(error)
	{
		printf("%s\n", FDC_error_message.buffer);
	}


	FDC_GameEngine_mainLoop(&engine);
}
